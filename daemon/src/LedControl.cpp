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

int LedControl::getBrightness() {

	vector<uint8_t> buffer_out;
	
	buffer_out.push_back(0xFF);
	buffer_out.push_back(CHECK_BRIGHTNESS);
	buffer_out.push_back(1);
	buffer_out.push_back(CHECK_BRIGHTNESS);

	vector<uint8_t> bc = mc->comunicate(buffer_out, 1, 4);

	if (bc.empty()) return -1000;
	if (bc[0] != 0xFF) return -1000;

	return (int)bc[3];
}

bool LedControl::isOn() {
	vector<uint8_t> buffer_out;
	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(CHECK_STATE);		// Instructions
	buffer_out.push_back(1);				// Size
	buffer_out.push_back(CHECK_STATE);

	vector<uint8_t> bc = mc->comunicate(buffer_out, 1, 4);

	if (bc.empty()) return 0;
	if (bc[0] != 0xFF) return 0;

	return (bool)bc[3];
}

//void LedControl::enableAll() {
//	return;
//}

//void LedControl::disableAll() {
//	return;
//}
#endif