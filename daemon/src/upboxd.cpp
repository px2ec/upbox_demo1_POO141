
#include "upboxd.h"

Dommo dm1;

// Scan devices an asign a dommo class
void scanDevices() {

	while (1){
		ModCom *mc = new ModCom;
		if (!(mc->isAssigned())){
			delete mc;
			break;	
		}
		cout << "Device found" << endl;
		cout << "Device description: " << mc->getModDescription() << endl;

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

	cout << "Dommo's devices:" << endl;

	for (int i = 0; i < dm1.getModDevsCount(); ++i) {
		cout << mdlist[i]->getDescription() << endl;
	}
}

// Return json as string to webapp
string getAllList() {

	json_object *jobj = json_object_new_object();
	
	json_object *jstring = json_object_new_string("RQST_ALL");
	json_object_object_add(jobj, "INTR", jstring);

	json_object *jint = json_object_new_int(dm1.getModDevsCount());
	json_object_object_add(jobj, "N_DEV", jint);

	if (dm1.getModDevsCount() == 0) return string(json_object_to_json_string(jobj));

	vector<ModDev*> mdlist = dm1.getAllModDevs();

	json_object *jarray = json_object_new_array();

	for (int i = 0; i < dm1.getModDevsCount(); ++i) {
		if ((mdlist[i]->getModCom())->getModDescription() == "LED_CTRL") {
			LedControl *lctrl = (LedControl *)mdlist[i];
			json_object *jobjLC = json_object_new_object();
			
			json_object *jintID = json_object_new_int(mdlist[i]->getID());
			json_object_object_add(jobjLC, "dev_id", jintID);
			
			json_object *jintType = json_object_new_int(2);
			json_object_object_add(jobjLC, "type", jintType);
			
			json_object *jintIntesity = json_object_new_int(lctrl->getBrightness());
			json_object_object_add(jobjLC, "intensity", jintIntesity);
 			
 			json_object *jstrName = json_object_new_string("Ilumanicion");
			json_object_object_add(jobjLC, "name", jstrName);
 			
 			json_object *jstrSts = json_object_new_boolean(lctrl->isOn());
			json_object_object_add(jobjLC, "status", jstrSts);
 			
 			json_object *jstrDescription = json_object_new_string((mdlist[i]->getDescription()).c_str());
			json_object_object_add(jobjLC, "description", jstrDescription);

			json_object_array_add(jarray,jobjLC);

		}else if ((mdlist[i]->getModCom())->getModDescription() == "TMP_SENS") {
			TempSensor *tmpsens = (TempSensor *)mdlist[i];
			json_object *jobjLC = json_object_new_object();
			
			json_object *jintID = json_object_new_int(mdlist[i]->getID());
			json_object_object_add(jobjLC, "dev_id", jintID);
			
			json_object *jintType = json_object_new_int(1);
			json_object_object_add(jobjLC, "type", jintType);
			
			json_object *jintTemp = json_object_new_int(tmpsens->getTempValue());
			json_object_object_add(jobjLC, "temperature", jintTemp);
 			
 			json_object *jstrName = json_object_new_string("Temperatura");
			json_object_object_add(jobjLC, "name", jstrName);
 			
 			json_object *jstrSts = json_object_new_boolean(1);
			json_object_object_add(jobjLC, "status", jstrSts);
 			
 			json_object *jstrDescription = json_object_new_string((mdlist[i]->getDescription()).c_str());
			json_object_object_add(jobjLC, "description", jstrDescription);

			json_object_array_add(jarray,jobjLC);
		}else if ((mdlist[i]->getModCom())->getModDescription() == "ACT_RELE") {
			ActuatorRele *actr = (ActuatorRele *)mdlist[i];
			json_object *jobjLC = json_object_new_object();
			
			json_object *jintID = json_object_new_int(mdlist[i]->getID());
			json_object_object_add(jobjLC, "dev_id", jintID);
			
			json_object *jintType = json_object_new_int(2);
			json_object_object_add(jobjLC, "type", jintType);
			
			 			
 			json_object *jstrName = json_object_new_string("Actuador");
			json_object_object_add(jobjLC, "name", jstrName);
 			
 			json_object *jstrSts = json_object_new_boolean(actr->isOn());
			json_object_object_add(jobjLC, "status", jstrSts);
 			
 			json_object *jstrDescription = json_object_new_string((mdlist[i]->getDescription()).c_str());
			json_object_object_add(jobjLC, "description", jstrDescription);

			json_object_array_add(jarray,jobjLC);
		}
	}

	json_object_object_add(jobj, "DEV_LIST", jarray);

	return string(json_object_to_json_string(jobj));
}

string setOnLed(json_object * jobj) {
	int dev_id = getIntFromKey(jobj, "dev_id");
	ModDev *md = dm1.getModDev(dev_id);
	if ((md->getModCom())->getModDescription() == "LED_CTRL") {
		LedControl *lctrl = (LedControl *)md;
		lctrl->turnOn();
		return "OK";
	}
	return "FAIL";
}

string setOffLed(json_object * jobj) {
	int dev_id = getIntFromKey(jobj, "dev_id");
	ModDev *md = dm1.getModDev(dev_id);
	if ((md->getModCom())->getModDescription() == "LED_CTRL") {
		LedControl *lctrl = (LedControl *)md;
		lctrl->turnOff();
		return "OK";
	}
	return "FAIL";
}

string setOnAct(json_object * jobj) {
	int dev_id = getIntFromKey(jobj, "dev_id");
	ModDev *md = dm1.getModDev(dev_id);
	if ((md->getModCom())->getModDescription() == "ACT_RELE") {
		ActuatorRele *actr = (ActuatorRele *)md;
		actr->enableRele();
		return "OK";
	}
	return "FAIL";
}

string setOffAct(json_object * jobj) {
	int dev_id = getIntFromKey(jobj, "dev_id");
	ModDev *md = dm1.getModDev(dev_id);
	if ((md->getModCom())->getModDescription() == "ACT_RELE") {
		ActuatorRele *actr = (ActuatorRele *)md;
		actr->disableRele();
		return "OK";
	}
	return "FAIL";
}

string setLedBrightness(json_object * jobj) {
	int dev_id = getIntFromKey(jobj, "dev_id");
	ModDev *md = dm1.getModDev(dev_id);
	if ((md->getModCom())->getModDescription() == "LED_CTRL") {
		LedControl *lctrl = (LedControl *)md;
		lctrl->setBrightness(getIntFromKey(jobj, "intensity"));
		return "OK";
	}
	return "FAIL";
}

// Return json as string
string getTemp(json_object * jobj) {
	int dev_id = getIntFromKey(jobj, "dev_id");
	ModDev *md = dm1.getModDev(dev_id);
	if (md == NULL) return "FAIL";

	json_object *jobjTmp = json_object_new_object();
	
	json_object *jstring = json_object_new_string("GET_TEMP");
	json_object_object_add(jobjTmp, "INTR", jstring);

	json_object *jintID = json_object_new_int(md->getID());
	json_object_object_add(jobjTmp, "dev_id", jintID);

	if ((md->getModCom())->getModDescription() == "TMP_SENS") {
		TempSensor *tmpsens = (TempSensor *)md;

		json_object *jintTemp = json_object_new_int(tmpsens->getTempValue());
		json_object_object_add(jobjTmp, "temperature", jintTemp);

		return string(json_object_to_json_string(jobjTmp));
	}
	return "FAIL";
}

// WebApp's instructions
string getReturn(json_object * jobj) {
	string intr = getStrFromKey(jobj, "INTR");
	if (intr == "RQST_ALL") {
		return getAllList();
	}else if (intr == "ONLED") {
		return setOnLed(jobj);
	}else if (intr == "OFFLED") {
		return setOffLed(jobj);
	}else if (intr == "SET_INTENSITY") {
		return setLedBrightness(jobj);
	}else if (intr == "ONACT") {
		return setOnAct(jobj);
	}else if (intr == "OFFACT") {
		return setOffAct(jobj);
	}else if (intr == "GET_TEMP") {
		return getTemp(jobj);
	}
	return "FAIL";
}

int main(int argc, char const *argv[]) {
	
	scanDevices();
	
	int status;
	struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

	// The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
	// to by hints must contain either 0 or a null pointer, as appropriate." When a struct
	// is created in c++, it will be given a block of memory. This memory is not nessesary
	// empty. Therefor we use the memset function to make sure all fields are NULL.
	memset(&host_info, 0, sizeof host_info);

	std::cout << "Setting up the structs..."  << std::endl;

	host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
	host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
	host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

	// Now fill up the linked list of host_info structs with google's address information.
	status = getaddrinfo(NULL, "5556", &host_info, &host_info_list);
	// getaddrinfo returns 0 on succes, or some other value when an error occured.
	// (translated into human readable text by the gai_gai_strerror function).
	if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;


	std::cout << "Creating a socket..."  << std::endl;
	int socketfd ; // The socket descripter
	socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
					  host_info_list->ai_protocol);
	if (socketfd == -1)  std::cout << "socket error " ;

	std::cout << "Binding socket..."  << std::endl;
	// we use to make the setsockopt() function to make sure the port is not in use
	// by a previous execution of our code. (see man page for more information)
	int yes = 1;
	status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
	if (status == -1)  std::cout << "bind error" << std::endl ;

	std::cout << "Listen()ing for connections..."  << std::endl;
	status =  listen(socketfd, 5);
	if (status == -1)  std::cout << "listen error" << std::endl ;


	int new_sd;
	struct sockaddr_storage their_addr;
	socklen_t addr_size = sizeof(their_addr);
	new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
	if (new_sd == -1)
	{
		std::cout << "listen error" << std::endl ;
	}
	else
	{
		std::cout << "Connection accepted. Using new socketfd : "  <<  new_sd << std::endl;
	}

	while(1){
		std::cout << "Waiting to recieve data..."  << std::endl;
		ssize_t bytes_recieved;
		char incomming_data_buffer[1000];
		bytes_recieved = recv(new_sd, incomming_data_buffer, 1000, 0);
		// If no data arrives, the program will just wait here until some data arrives.
		if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
		if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
		std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
		incomming_data_buffer[bytes_recieved] = '\0';
		//std::cout << incomming_data_buffer << std::endl;

		if (incomming_data_buffer[0] != '{') continue;
			
		// JSON-----
		json_object * jobj = json_tokener_parse(incomming_data_buffer);     
		//json_parse(jobj);

		string to_return = getReturn(jobj);

		// ---------

		std::cout << "send()ing back a message..."  << std::endl;
		char msg[10000];
		strcpy(msg, to_return.c_str()); 
		int len;
		ssize_t bytes_sent;
		len = to_return.size();
		bytes_sent = send(new_sd, msg, len, 0);
	}

	std::cout << "Stopping server..." << std::endl;
	freeaddrinfo(host_info_list);
	close(new_sd);
	close(socketfd);

return 0 ;
	

}