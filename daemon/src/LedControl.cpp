// by Pedro Espinoza


#ifndef LEDCONTROL_CPP
#define LEDCONTROL_CPP

#include "LedControl.h"

LedControl::LedControl(void):ModDev() {
	return;
}

LedControl::~LedControl(void) {
	return;
}

void LedControl::turnOn() {

	vector<uint8_t> buffer_out;

	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(ENABLE_INTR);		// Instructions
	buffer_out.push_back(1);				// Size
	buffer_out.push_back(1);	// Index

	mc->comunicate(buffer_out);
}

void LedControl::turnOff() {

	vector<uint8_t> buffer_out;
	
	buffer_out.push_back(0xFF);
	buffer_out.push_back(DISABLE_INTR);
	buffer_out.push_back(1);
	buffer_out.push_back(1);

	mc->comunicate(buffer_out);
}

string LedControl::getDescription() {
	stringstream stream; 
	stream << this->getID(); 
	return "LedControl_" + stream.str();
}

string LedControl::getStatus() {
	if (!(this->isEnabled())){
		return string("Disbled");
	}

	return "Enabled";
}

void LedControl::setBrightness(int value) {

	vector<uint8_t> buffer_out;
	
	buffer_out.push_back(0xFF);
	buffer_out.push_back(SET_BRIGHTNESS);
	buffer_out.push_back(1);
	buffer_out.push_back((uint8_t) value);

	mc->comunicate(buffer_out);
}

//void LedControl::enableAll() {
//	return;
//}

//void LedControl::disableAll() {
//	return;
//}
#endif