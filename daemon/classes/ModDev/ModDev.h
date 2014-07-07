
#ifndef MODDEV_H
#define MODDEV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <string>

#include "ModCom.h"

#define ENABLE_INTR		48
#define DISABLE_INTR	56

#define	ENABLE_ALL		44
#define	DISABLE_ALL		52

class ModDev {
	
	ModCom mc;

	bool enable = 1;

	uint8_t buffer_in[255];
	char buffer_out[255];

	static int n_int;

public:

	ModDev();
	~ModDev(void);

	void asociateModCom(ModCom mc_arg);

	virtual string getDescription();

	virtual string getStatus();

	void enable();
	void disable();

	int getInstanceCount();
};
#endif