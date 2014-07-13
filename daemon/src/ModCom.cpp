// by Pedro Espinoza

#ifndef MODCOM_CPP
#define MODCOM_CPP

#include "ModCom.h"

vector<string> ModCom::devDescriptionList;

ModCom::ModCom(void) {
	assigned = 0;
	dd = "";
	char ttyport[33];
	char *serial_name;
	vector<string>::iterator redodev;

	// Search ttyUSB_'N' serial devices
	for(int n = 0; n < 10; n++){
		sprintf(ttyport, "/dev/ttyUSB%d", n);   
		serial_name = strdup(ttyport);
		fd = serialport_init(serial_name, 9600);
		if (fd != -1){
			redodev = find(devDescriptionList.begin(), devDescriptionList.end(), string(ttyport));
			if (redodev == devDescriptionList.end() || devDescriptionList.size() == 0) {
				if (this->checkdev()){
					dd = string(ttyport);
					devDescriptionList.push_back(string(ttyport));
					assigned = 1;
					return;
				}
			}
		}
		serialport_close(fd);
	}

	// Search ttyACM_'N' arduino serial devices
	for(int n = 0; n < 10; n++){
		sprintf(ttyport, "/dev/ttyACM%d", n);  
		serial_name = strdup(ttyport);
		fd = serialport_init(serial_name, 9600);
		if (fd != -1){
			redodev = find(devDescriptionList.begin(), devDescriptionList.end(), string(ttyport));
			if (redodev == devDescriptionList.end() || devDescriptionList.size() == 0) {
				if (this->checkdev()){
					dd = string(ttyport);
					devDescriptionList.push_back(string(ttyport));
					assigned = 1;
					return;
				}
			}
		}
		serialport_close(fd);
	}

	// Search rfcomm_'N' arduino bluetooth devices
	for(int n = 0; n < 10; n++){
		sprintf(ttyport, "/dev/rfcomm%d", n);  
		serial_name = strdup(ttyport);
		fd = serialport_init(serial_name, 9600);
		if (fd != -1){
			redodev = find(devDescriptionList.begin(), devDescriptionList.end(), string(ttyport));
			if (redodev == devDescriptionList.end() || devDescriptionList.size() == 0) {
				if (this->checkdev()){
					dd = string(ttyport);
					devDescriptionList.push_back(string(ttyport));
					assigned = 1;
					return;
				}
			}
		}
		serialport_close(fd);
	}
}

ModCom::~ModCom(void) {
	if (fd >= 0) serialport_close(fd);
	if (dd == "" || devDescriptionList.size() == 0) return;
	vector<string>::iterator redodev;
	redodev = find(devDescriptionList.begin(), devDescriptionList.end(), dd);
	devDescriptionList.erase(redodev);
}

bool ModCom::isAssigned() {
	return assigned;
}

string ModCom::getModDescription() {
	return md;
}

string ModCom::getDevDescription() {
	return dd;
}

vector<uint8_t> ModCom::comunicate(vector<uint8_t> buffer) {
	return this->comunicate(buffer, 0, 0);
}

vector<uint8_t> ModCom::comunicate(vector<uint8_t> buffer, bool readdata, int sizeread) {
	uint8_t *buffer_out = &(buffer[0]);

	uint8_t buffer_in[255];

	serialport_flush(fd);
	serialport_write(fd, (char*)buffer_out);

	if (!readdata) {
		vector<uint8_t> toreturn;
		return toreturn;
	} // if only send
	
	//serial_read(fd, buffer_in, 1, DEF_TIMEOUT);
	
	serialport_read(fd, buffer_in, sizeread, DEF_TIMEOUT);

	if (buffer_in[0] != 0xFF) {
		vector<uint8_t> toreturn;
		return toreturn;
	}
	
	vector<uint8_t> vr(buffer_in, buffer_in + sizeread);
	
	return vr;
}

// private functions

void ModCom::init() {
	vector<uint8_t> buffer_out;
	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(INIT_DEV);		// Instructions
	buffer_out.push_back(1);				// Size
	buffer_out.push_back(INIT_DEV);

	this->comunicate(buffer_out);

	usleep(2000*1000);
}

bool ModCom::checkdev() {
	this->init();
	vector<uint8_t> buffer_out;
	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(CHECK_DEV);		// Instructions
	buffer_out.push_back(1);				// Size
	buffer_out.push_back(CHECK_DEV);

	vector<uint8_t> bc = this->comunicate(buffer_out, 1, 11);

	if (bc.empty()) return 0;

	if (bc[0] != 0xFF && bc[1] != CHECK_DEV){
		return 0;
	}

	//char *devd = &(bc[3]);
	md = string(&bc[0] + 3, &bc[0] + 11);

	return 1;
}

#endif