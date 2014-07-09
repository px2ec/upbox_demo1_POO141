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

void ActuatorRele::enableRele(int index) {

	vector<uint8_t> buffer_out;

	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(ENABLE_INTR);		// Instructions
	buffer_out.push_back(1);				// Size
	buffer_out.push_back((uint8_t)index);	// Index

	mc.comunicate(buffer_out);
}

void ActuatorRele::disableRele(int index) {

	vector<uint8_t> buffer_out;
	
	buffer_out.push_back(0xFF);
	buffer_out.push_back(DISABLE_INTR);
	buffer_out.push_back(1);
	buffer_out.push_back((uint8_t)index);

	mc.comunicate(buffer_out);
}

string ActuatorRele::getDescription() {
	stringstream stream; 
	stream << this->getID(); 
	return "ActuatorRele_" + stream.str();
}

string ActuatorRele::getStatus() {
	if (this->isEnabled()){
		return "Enabled";
	}
	return string("Disbled");
}

//void ActuatorRele::enableAll() {
//	return;
//}

//void ActuatorRele::disableAll() {
//	return;
//}
#endif