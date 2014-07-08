// by Pedro Espinoza

#ifndef MODDEV_CPP
#define MODDEV_CPP

#include "ModDev.h"

ModDev::ModDev() {
	my_id = n_inst++;
}

ModDev::~ModDev(void) {
	n_inst--;
}

void ModDev::enable() {
	enabled = 1
}

void ModDev::disable() {
	enabled = 0
}

void ModDev::asociateModCom(ModCom mc_arg) {
	mc = mc_arg;
}

int ModDev::getInstanceCount() {
	return n_inst;
}

int ModDev::getID() {
	return my_id;
}

#endif