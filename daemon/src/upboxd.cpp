
#include "upboxd.h"

Dommo dm1;

/*printing the value corresponding to boolean, double, integer and strings*/
void print_json_value(json_object *jobj){
	enum json_type type;
	printf("type: %d ",type);
	type = json_object_get_type(jobj); /*Getting the type of the json object*/
	switch (type) {
		case json_type_boolean: printf("json_type_boolean\n");
			printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
			break;
		case json_type_double: printf("json_type_double\n");
			printf("          value: %lf\n", json_object_get_double(jobj));
			break;
		case json_type_int: printf("json_type_int\n");
			printf("          value: %d\n", json_object_get_int(jobj));
			break;
		case json_type_string: printf("json_type_string\n");
			printf("          value: %s\n", json_object_get_string(jobj));
			break;
	}
}

void json_parse_array( json_object *jobj, char *key) {
	void json_parse(json_object * jobj); /*Forward Declaration*/
	enum json_type type;

	json_object *jarray = jobj; /*Simply get the array*/
	if(key) {
		jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
	}

	int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
	printf("Array Length: %d\n", arraylen);
	int i;
	json_object * jvalue;

	for (i=0; i< arraylen; i++){
		jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
		type = json_object_get_type(jvalue);
		if (type == json_type_array) {
			json_parse_array(jvalue, NULL);
		}
		else if (type != json_type_object) {
			printf("value[%d]: ", i);
			print_json_value(jvalue);
		}
		else {
			json_parse(jvalue);
		}
	}
}

/*Parsing the json object*/
void json_parse(json_object * jobj) {
	enum json_type type;
	json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
		printf("key: %s\n",key);
		printf("type: %d ",type);
		type = json_object_get_type(val);
		switch (type) {
			case json_type_boolean: 
			case json_type_double: 
			case json_type_int: 
			case json_type_string: print_json_value(val);
				break; 
			case json_type_object: printf("json_type_object\n");
				jobj = json_object_object_get(jobj, key);
				json_parse(jobj); 
				break;
			case json_type_array: printf("type: json_type_array, ");
				json_parse_array(jobj, key);
				break;
		}
	}
} 

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
	while(1){
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

		std::cout << "Waiting to recieve data..."  << std::endl;
		ssize_t bytes_recieved;
		char incomming_data_buffer[1000];
		bytes_recieved = recv(new_sd, incomming_data_buffer, 1000, 0);
		// If no data arrives, the program will just wait here until some data arrives.
		if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
		if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
		std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
		incomming_data_buffer[bytes_recieved] = '\0';
		std::cout << incomming_data_buffer << std::endl;

		// JSON-----
		json_object * jobj = json_tokener_parse(incomming_data_buffer);     
		json_parse(jobj);
		// ---------

		std::cout << "send()ing back a message..."  << std::endl;
		char msg[] = "thank you.";
		int len;
		ssize_t bytes_sent;
		len = strlen(msg);
		bytes_sent = send(new_sd, msg, len, 0);
	}

	std::cout << "Stopping server..." << std::endl;
	freeaddrinfo(host_info_list);
	close(new_sd);
	close(socketfd);

return 0 ;
	

}