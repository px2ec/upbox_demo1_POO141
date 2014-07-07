// by Pedro Espinoza

#ifndef MODDEV_CPP
#define MODDEV_CPP

#include "ModDev.h"

ModDev::ModDev() {
	n_int++;
}

ModDev::~ModDev(void) {
	n_int--;
}

void ModDev::enable() {
	enable = 1
}

void ModDev::disable() {
	enable = 0
}

void ModDev::asociateModCom(ModCom mc_arg) {
	mc = mc_arg;
}

int ModDev::getInstanceCount() {
	return n_int;
}

#endif