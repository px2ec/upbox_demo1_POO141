
#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

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

#define RQST_TEMP		15

class TempSensor : public ModDev {
	
public:
	TempSensor(void);
	~TempSensor(void);

	int getTempValue();

	string getDescription();
	string getStatus();

};
#endif