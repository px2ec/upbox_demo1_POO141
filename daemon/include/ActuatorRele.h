
#ifndef ACTUATORRELE_H
#define ACTUATORRELE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#include "ModCom.h"
#include "ModDev.h"

#define ENABLE_INTR		48
#define DISABLE_INTR	56

#define	ENABLE_ALL		44
#define	DISABLE_ALL		52

class ActuatorRele : public ModDev {
	
	int n_rele;

public:
	ActuatorRele(void);
	~ActuatorRele(void);

	void enableRele(int index);
	void disableRele(int index);

	//void enableRele(int index);
	//void disableRele(int index);
	//void enableAll();
	//void disableAll();

	string getDescription();
	string getStatus();

};
#endif