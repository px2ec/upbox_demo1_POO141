
#ifndef DOMMO_H
#define DOMMO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#include "ModDev.h"
#include "ModCom.h"

#define ENABLE_INTR		48
#define DISABLE_INTR	56

#define	ENABLE_ALL		44
#define	DISABLE_ALL		52

class Dommo {
	
	int n_md;
	vector<ModDev*> myModDevs;

public:
	Dommo(void);
	~Dommo(void);

	vector<ModDev*> getAllModDevs();
	ModDev *getModDev(int id);
	void addModdev(ModDev &md);
	int getModDevsCount();
};
#endif