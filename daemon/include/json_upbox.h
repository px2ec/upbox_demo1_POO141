
#include <json/json.h>
#include <stdio.h>

#include <string>

using namespace std;

string getStrFromKey(json_object * jobj, string skey);
int getIntFromKey(json_object * jobj, string skey);
//int getBooleanFromKey(json_object * jobj, string skey);