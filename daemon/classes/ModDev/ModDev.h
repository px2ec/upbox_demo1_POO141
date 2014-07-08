
#ifndef MODDEV_H
#define MODDEV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "ModCom.h"

#define ENABLE_INTR		48
#define DISABLE_INTR	56

#define	ENABLE_ALL		44
#define	DISABLE_ALL		52

class ModDev {
	
	ModCom mc;

	bool enabled = 1;

	vector<uint8_t> buffer_in;
	vector<uint8_t> buffer_out;

	static int n_inst = 0;

	int my_id;

public:

	ModDev(void);
	~ModDev(void);

	void asociateModCom(ModCom mc_arg);

	virtual string getDescription();
	virtual string getStatus();

	void enable();
	void disable();

	int getID();

	int getInstanceCount();
};
#endif