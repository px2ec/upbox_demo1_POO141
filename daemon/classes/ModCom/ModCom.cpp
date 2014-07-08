// by Pedro Espinoza

#ifndef MODCOM_CPP
#define MODCOM_CPP

#include "ModCom.h"

ModCom::ModCom(void) {
	char ttyport[33];
	vector<string>::iterator redodev;

	// Search ttyUSB_'N' serial devices
	for(int n = 0; n < 10; n++){
		sprintf(ttyport, "/dev/ttyUSB%d", n);   
		fd = serial_open(ttyport, B1000000);
		if (fd != -1){
			redodev = devDescriptionList.find(devDescriptionList.begin(), devDescriptionList.end(), string(ttyport));
			if (redodev == devDescriptionList.end()) {
				if (checkdev()){
					dd = string(ttyport);
					devDescriptionList.push_back(dd);
					assigned = 1;
					return;
				}
			}
		}
		serial_close(fd);
	}

	// Search ttyACM_'N' arduino serial devices
	for(int n = 0; n < 10; n++){
		sprintf(ttyport, "/dev/ttyACM%d", n);   
		fd = serial_open(ttyport, B1000000);
		if (fd != -1){
			redodev = devDescriptionList.find(devDescriptionList.begin(), devDescriptionList.end(), string(ttyport));
			if (redodev == devDescriptionList.end()) {
				if (this->checkdev()){
					dd = string(ttyport);
					devDescriptionList.push_back(dd);
					assigned = 1;
					return;
				}
			}
		}
		serial_close(fd);
	}
}

ModCom::~ModCom(void) {
	if (fd >= 0) serial_close(fd);
	return;
}

bool ModCom::isAssigned() {
	return asigned;
}

string ModCom::getModDescription() {
	return md;
}

string ModCom::getDevDescription() {
	return dd;
}

vector<uint8_t> ModCom::comunicate(vector<uint8_t> buffer) {
	this->comunicate(buffer, 0, 0);
}

vector<uint8_t> ModCom::comunicate(vector<uint8_t> buffer, bool readdata, int sizeread) {
	uint8_t *buffer_out = &(buffer[0]);

	uint8_t buffer_in[255];

	serial_io_flush(fd);
	serial_send(fd, buffer_out, buffer.size());

	if (!readdata) return NULL; // if only send

	serial_read(fd, buffer_in, sizeread, DEF_TIMEOUT);

	if (buffer_in[0] != 0xFF) {
		return NULL;
	}
	
	vector<int> vr(buffer_in, buffer_in + sizeread);
	
	return vr;
}

// private functions
bool ModCom::checkdev() {
	vector<uint8_t> buffer_out;
	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(CHECK_DEV);		// Instructions
	buffer_out.push_back(1);				// Size

	vector<uint8_t> bc = this->comunicate(buffer_out, 1, 11);

	if (bc[0] != 0xFF && bc[1] != CHECK_DEV){
		return 0;
	}

	char *devd = &(bc[3]);
	dd = string(devd);

	return 1;
}

#endif