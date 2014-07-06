// by Pedro Espinoza


#ifndef ACTUATORRELE_CPP
#define ACTUATORRELE_CPP

#include "ActuatorRele.h"

ActuatorRele::ActuatorRele(char *serial_name, int c_suckers) {
	// Open serial port (in linux)
	fd = serial_open(serial_name, B9600);
	if (fd < 0) printf("PORT ERROR\n");

	n_suckers = c_suckers;
}

ActuatorRele::~ActuatorRele(void) {
	serial_close(fd);
}

void ActuatorRele::enableRele(int index) {
	buffer_out[0] = 0xFF;			// Header
	buffer_out[1] = ENABLE_INTR;	// Instructions
	buffer_out[2] = 1;				// Suctions cups numbers
	buffer_out[3] = (uint8_t)index;	// Index

	serial_io_flush(fd);
	serial_send(fd, buffer_out, 4);
}

void ActuatorRele::disableRele(int index) {
	buffer_out[0] = 0xFF;
	buffer_out[1] = DISABLE_INTR;
	buffer_out[2] = 1;
	buffer_out[3] = (uint8_t)index;

	serial_io_flush(fd);
	serial_send(fd, buffer_out, 4);
}

void ActuatorRele::enableAll() {
	buffer_out[0] = 0xFF;
	buffer_out[1] = ENABLE_ALL;
	buffer_out[2] = 1;
	buffer_out[3] = 1;

	serial_io_flush(fd);
	serial_send(fd, buffer_out, 4);
}

void ActuatorRele::disableAll() {
	buffer_out[0] = 0xFF;
	buffer_out[1] = DISABLE_ALL;
	buffer_out[2] = 1;
	buffer_out[3] = 1;

	serial_io_flush(fd);
	serial_send(fd, buffer_out, 4);
}
#endif