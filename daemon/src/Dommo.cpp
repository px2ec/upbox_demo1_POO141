// by Pedro Espinoza


#ifndef DOMMO_CPP
#define DOMMO_CPP

#include "Dommo.h"

Dommo::Dommo(void) {
	return;
}

Dommo::~Dommo(void) {
	for (int i = 0; i < n_md; ++i){
		delete myModDevs[i];
	}
}
vector<ModDev*> Dommo::getAllModDevs() {
	return myModDevs;
}

ModDev *Dommo::getModDev(int id) {
	for (int i = 0; i < (int)(myModDevs.size()); ++i){
		if (id == (int)(myModDevs[i]->getID())){
			return myModDevs[i];
		}
	}
	return NULL;
}

void Dommo::addModdev(ModDev &md) {
	myModDevs.push_back(&md);
}
int Dommo::getModDevsCount() {
	return (int)(myModDevs.size());
}

#endif