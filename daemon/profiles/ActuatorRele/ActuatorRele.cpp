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
	buffer_out.push_back(0xFF);				// Header
	buffer_out.push_back(ENABLE_INTR);		// Instructions
	buffer_out.push_back(1);				// Size
	buffer_out.push_back((uint8_t)index);	// Index

	mc.comunicate(buffer_out, 0);
}

void ActuatorRele::disableRele(int index) {
	buffer_out.push_back(0xFF);
	buffer_out.push_back(DISABLE_INTR);
	buffer_out.push_back(1);
	buffer_out.push_back((uint8_t)index);

	mc.comunicate(buffer_out, 0);
}

string ActuatorRele::getDescription() {
	stringstream stream; 
	stream << my_id; 
	return "ActuatorRele_" + stream.str();
}

string ActuatorRele::getStatus() {
	if (enabled){
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