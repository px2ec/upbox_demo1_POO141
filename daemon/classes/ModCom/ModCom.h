
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
#include <algorithm>

#define DEF_TIMEOUT		100000
#define CHECK_DEV		16

using namespace std;

class ModCom {
	int fd;

	bool assigned;

	static vector<string> devDescriptionList;

	string dd;
	string md;

	bool checkdev();

public:

	ModCom(void);
	~ModCom(void);

	vector<uint8_t> comunicate(vector<uint8_t> buffer);
	vector<uint8_t> comunicate(vector<uint8_t> buffer, bool returndata, int sizeread);

	bool isAssigned();

	string getModDescription();
	string getDevDescription();
};

#endif