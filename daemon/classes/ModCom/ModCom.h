
#ifndef MODCOM_H
#define MODCOM_H

extern "C" {
	#include "serial.h"
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdint.h>
#include <iostream>
#include <vector>

class ModCom {
	int fd;

	static vector<string> devDescriptionList;

public:

	ModCom();
	~ModCom(void);

	vector<uint8_t> comunicate(vector<uint8_t>, bool returndata);

	int getID();

	bool scan();

	string getDevDescription();
};

#endif