
#ifndef MODDEV_H
#define MODDEV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "ModCom.h"

#define ENABLE_INTR		48
#define DISABLE_INTR	56

#define	ENABLE_ALL		44
#define	DISABLE_ALL		52
#define CHECK_STATE		42

using namespace std;

class ModDev {

	static int n_inst;

protected:

	ModCom mc;

	bool enabled;

	int my_id;

public:

	ModDev(void);
	virtual ~ModDev(void);

	void asociateModCom(ModCom &mc_arg);
	ModCom getModCom();

	virtual string getDescription(){return "";};
	virtual string getStatus(){return "";};

	void setEnable();
	void setDisable();
	bool isEnabled();

	int getID();

	int getInstanceCount();
};
#endif