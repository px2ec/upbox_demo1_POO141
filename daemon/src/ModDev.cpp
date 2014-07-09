// by Pedro Espinoza

#ifndef MODDEV_CPP
#define MODDEV_CPP

#include "ModDev.h"

int ModDev::n_inst;

ModDev::ModDev(void) {
	my_id = n_inst++;
	enabled = 1;
}

ModDev::~ModDev(void) {
	n_inst--;
}

void ModDev::setEnable() {
	enabled = 1;
}

void ModDev::setDisable() {
	enabled = 0;
}

bool ModDev::isEnabled() {
	return enabled;
}

void ModDev::asociateModCom(ModCom &mc_arg) {
	mc = mc_arg;
}

ModCom ModDev::getModCom() {
	return mc;
}

int ModDev::getInstanceCount() {
	return n_inst;
}

int ModDev::getID() {
	return my_id;
}

#endif