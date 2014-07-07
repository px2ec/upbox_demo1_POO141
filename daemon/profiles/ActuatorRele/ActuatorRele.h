
#ifndef ACTUATORRELE_H
#define ACTUATORRELE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>

#include "ModCom.h"

#define ENABLE_INTR		48
#define DISABLE_INTR	56

#define	ENABLE_ALL		44
#define	DISABLE_ALL		52

class ActuatorRele : public ModDev{
	
	ModCom mc;

	int n_rele;

public:

	ActuatorRele(char *, int);
	~ActuatorRele(void);

	void enableRele(int index);
	void disableRele(int index);
	void enableAll();
	void disableAll();

};
#endif