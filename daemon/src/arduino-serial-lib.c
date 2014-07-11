//
// arduino-serial-lib -- simple library for reading/writing serial ports
//
// 2006-2013, Tod E. Kurt, http://todbot.com/blog/
//

#include "arduino-serial-lib.h"

#include <stdio.h>    // Standard input/output definitions 
#include <unistd.h>   // UNIX standard function definitions 
#include <fcntl.h>    // File control definitions 
#include <errno.h>    // Error number definitions 
#include <termios.h>  // POSIX terminal control definitions 
#include <string.h>   // String function definitions 
#include <time.h>
#include <sys/ioctl.h>
#include <sys/select.h>

// uncomment this to debug reads
//#define SERIALPORTDEBUG 

// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
// and a baud rate (bps) and connects to that port at that speed and 8N1.
// opens the port in fully raw mode so you can send binary data.
// returns valid fd, or -1 on error
int serialport_init(const char* serialport, int baud)
{
	struct termios toptions;
	int fd;
	
	//fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
	fd = open(serialport, O_RDWR | O_NONBLOCK );
	
	if (fd == -1)  {
#ifdef SERIALPORTDEBUG 
		perror("serialport_init: Unable to open port ");
#endif
		return -1;
	}
	
	//int iflags = TIOCM_DTR;
	//ioctl(fd, TIOCMBIS, &iflags);     // turn on DTR
	//ioctl(fd, TIOCMBIC, &iflags);    // turn off DTR

	if (tcgetattr(fd, &toptions) < 0) {
#ifdef SERIALPORTDEBUG 
		perror("serialport_init: Couldn't get term attributes");
#endif
		return -1;
	}
	speed_t brate = baud; // let you override switch below if needed
	switch(baud) {
	case 4800:   brate=B4800;   break;
	case 9600:   brate=B9600;   break;
#ifdef B14400
	case 14400:  brate=B14400;  break;
#endif
	case 19200:  brate=B19200;  break;
#ifdef B28800
	case 28800:  brate=B28800;  break;
#endif
	case 38400:  brate=B38400;  break;
	case 57600:  brate=B57600;  break;
	case 115200: brate=B115200; break;
	}
	cfsetispeed(&toptions, brate);
	cfsetospeed(&toptions, brate);

	// 8N1
	toptions.c_cflag &= ~PARENB;
	toptions.c_cflag &= ~CSTOPB;
	toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8;
	// no flow control
	toptions.c_cflag &= ~CRTSCTS;

	//toptions.c_cflag &= ~HUPCL; // disable hang-up-on-close to avoid reset

	toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
	toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

	toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
	toptions.c_oflag &= ~OPOST; // make raw

	// see: http://unixwiz.net/techtips/termios-vmin-vtime.html
	toptions.c_cc[VMIN]  = 0;
	toptions.c_cc[VTIME] = 0;
	//toptions.c_cc[VTIME] = 20;
	
	tcsetattr(fd, TCSANOW, &toptions);
	if( tcsetattr(fd, TCSAFLUSH, &toptions) < 0) {
#ifdef SERIALPORTDEBUG 
		perror("init_serialport: Couldn't set term attributes");
#endif
		return -1;
	}

	return fd;
}

//
int serialport_close( int fd )
{
	return close( fd );
}

//
int serialport_writebyte( int fd, uint8_t b)
{
	int n = write(fd,&b,1);
	if( n!=1)
		return -1;
	return 0;
}

//
int serialport_write(int fd, const char* str)
{
	int len = strlen(str);
	int n = write(fd, str, len);
	if( n!=len ) {
#ifdef SERIALPORTDEBUG 
		perror("serialport_write: couldn't write whole string\n");
#endif
		return -1;
	}
	return 0;
}

//
int serialport_read_until(int fd, char* buf, char until, int buf_max, int timeout)
{
	char b[1];  // read expects an array, so we give it a 1-byte array
	int i=0;
	do { 
		int n = read(fd, b, 1);  // read a char at a time
		if( n==-1) return -1;    // couldn't read
		if( n==0 ) {
			usleep( 1 * 1000 );  // wait 1 msec try again
			timeout--;
			continue;
		}
#ifdef SERIALPORTDEBUG  
		printf("serialport_read_until: i=%d, n=%d b='%c'\n",i,n,b[0]); // debug
#endif
		buf[i] = b[0]; 
		i++;
	} while( b[0] != until && i < buf_max && timeout>0 );

	buf[i] = 0;  // null terminate the string
	return 0;
}

//
int serialport_read(int serial_fd, uint8_t *data, int size, int timeout_usec)
{
	fd_set fds;
	struct timeval timeout;
	int count=0;
	int ret;
	int n;
	
	//-- Wait for the data. A block of size bytes is expected to arrive
	//-- within the timeout_usec time. This block can be received as 
	//-- smaller blocks.
	do {
			//-- Set the fds variable to wait for the serial descriptor
			FD_ZERO(&fds);
			FD_SET (serial_fd, &fds);

			//-- Set the timeout in usec.
			timeout.tv_sec = 0;  
			timeout.tv_usec = timeout_usec;

			//-- Wait for the data
			ret=select (FD_SETSIZE,&fds, NULL, NULL,&timeout);

			//-- If there are data waiting: read it
			if (ret==1) {
				//-- Read the data (n bytes)
				n=read (serial_fd, &data[count], size-count); 

				//-- The number of bytes receives is increased in n
				count+=n;

				//-- The last byte is always a 0 (for printing the string data)
				data[count]=0;
			}

		//-- Repeat the loop until a data block of size bytes is received or
		//-- a timeout occurs
	} while (count<size && ret==1);

		//-- Return the number of bytes reads. 0 If a timeout has occurred.
	return count;
}

//
int serialport_flush(int fd)
{
	return tcflush(fd, TCIOFLUSH);
}
