// by Pedro Espinoza


#ifndef TEMPSENSOR_CPP
#define TEMPSENSOR_CPP

#include "TempSensor.h"

TempSensor::TempSensor(void):ModDev() {
	return;
}

TempSensor::~TempSensor(void) {
	return;
}

int TempSensor::getTempValue() {
	vector<uint8_t> buffer_out;
	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(RQST_TEMP);		// Instructions
	buffer_out.push_back(1);				// Size
	buffer_out.push_back(RQST_TEMP);

	vector<uint8_t> bc = mc->comunicate(buffer_out, 1, 4);

	if (bc.empty()) return -1000;
	if (bc[0] != 0xFF) return -1000;

	return (int)bc[3];
}

string TempSensor::getDescription() {
	stringstream stream; 
	stream << this->getID(); 
	return "TempSensor_" + stream.str();
}

string TempSensor::getStatus() {
	if (!(this->isEnabled())){
		return string("Disbled");
	}
	
	return "Enabled";
}

#endif