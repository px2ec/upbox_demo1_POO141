
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

using namespace std;

int main(int argc, char const *argv[]) {
	ModCom mc1;
	ModCom mc;
	cout << mc.getModDescription() << '\n';

	if (mc.getModDescription() == "ACT_RELE") {
		ActuatorRele actr;
		actr.asociateModCom(mc);
		actr.enableRele(1);
	}

	//printf("%d\n", (int)(mc.isAssigned()));
}