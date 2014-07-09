
#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>
#include <unistd.h>

extern "C" {
	#include "serial.h"
}

#include "ModCom.h"

using namespace std;

int main(int argc, char const *argv[]) {
	ModCom mc;

	cout << mc.getModDescription() << '\n';
	//printf("%d\n", (int)(mc.isAssigned()));
}