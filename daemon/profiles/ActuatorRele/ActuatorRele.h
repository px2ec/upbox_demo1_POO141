
#ifndef ACTUATORRELE_H
#define ACTUATORRELE_H

extern "C" {
	#include "serial.h"
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>

#define ENABLE_INTR		48
#define DISABLE_INTR	56

#define	ENABLE_ALL		44
#define	DISABLE_ALL		52

class ActuatorRele {
	int fd;

	int n_suckers;

	uint8_t buffer_in[255];
	char buffer_out[255];

public:

	ActuatorRele(char *, int);
	~ActuatorRele(void);

	void enableRele(int index);
	void disableRele(int index);

	void enableAll();
	void disableAll();

};
#endif