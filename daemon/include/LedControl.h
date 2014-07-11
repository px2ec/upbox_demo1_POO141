
#ifndef LEDCONTROL_H
#define LEDCONTROL_H

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
#define SET_BRIGHTNESS	12

class LedControl : public ModDev {
	
	int n_rele;

public:
	LedControl(void);
	~LedControl(void);

	void turnOn();
	void turnOff();
	//void turnOn(int index);
	//void turnOff(int index);
	void setBrightness(int value);

	string getDescription();
	string getStatus();

};
#endif