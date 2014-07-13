
#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>
#include <unistd.h>

#include "ModDev.h"
#include "ModCom.h"
#include "ActuatorRele.h"
#include "LedControl.h"
#include "TempSensor.h"

#include "Dommo.h"

using namespace std;

int main(int argc, char const *argv[]) {

	Dommo dm1;
	
	while (1){
		ModCom *mc = new ModCom;
		if (!(mc->isAssigned())){
			delete mc;
			break;	
		} 
		cout << mc->getModDescription() << '\n';

		if (mc->getModDescription() == "ACT_RELE") {
			ActuatorRele *actr = new ActuatorRele;
			actr->asociateModCom(*mc);
			dm1.addModdev(*actr);
		}else if (mc->getModDescription() == "LED_CTRL") {
			LedControl *lctrl = new LedControl;
			lctrl->asociateModCom(*mc);
			dm1.addModdev(*lctrl);
		}else if (mc->getModDescription() == "TMP_SENS") {
			TempSensor *tmpsens = new TempSensor;
			tmpsens->asociateModCom(*mc);
			dm1.addModdev(*tmpsens);
		}
	}

	vector<ModDev*> mdlist = dm1.getAllModDevs();

	for (int i = 0; i < dm1.getModDevsCount(); ++i) {
		cout << mdlist[i]->getDescription() << '\n';
	}
}