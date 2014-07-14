// by Pedro Espinoza


#ifndef ACTUATORRELE_CPP
#define ACTUATORRELE_CPP

#include "ActuatorRele.h"

ActuatorRele::ActuatorRele(void):ModDev() {
	return;
}

ActuatorRele::~ActuatorRele(void) {
	return;
}

void ActuatorRele::enableRele() {

	vector<uint8_t> buffer_out;

	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(ENABLE_INTR);		// Instructions
	buffer_out.push_back(1);				// Size
	buffer_out.push_back(1);				// Index

	mc->comunicate(buffer_out);
}

void ActuatorRele::disableRele() {

	vector<uint8_t> buffer_out;
	
	buffer_out.push_back(0xFF);
	buffer_out.push_back(DISABLE_INTR);
	buffer_out.push_back(1);
	buffer_out.push_back(1);

	mc->comunicate(buffer_out);
}

string ActuatorRele::getDescription() {
	stringstream stream; 
	stream << this->getID(); 
	return "ActuatorRele_" + stream.str();
}

string ActuatorRele::getStatus() {
	if (!(this->isEnabled())){
		return string("Disbled");
	}
	
	return "Enabled";
}

bool ActuatorRele::isOn() {
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

//void ActuatorRele::enableAll() {
//	return;
//}

//void ActuatorRele::disableAll() {
//	return;
//}
#endif