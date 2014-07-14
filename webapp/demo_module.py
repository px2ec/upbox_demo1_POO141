#!/usr/bin/python

import socket
import json

HOST = ''
PORT = 6000
ident = 1
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
devices = []
example_object_temp = {
                        'dev_id': 1,
                        'type': 1,
                        'status': 'on',
                        'name': 'Sala de reuniones / Temperatura',
                        'description': 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.',
                        'temperature': 20,
                    }
example_object_dimmer = {
                        'dev_id': 2,
                        'type': 2,
                        'status': 'on',
                        'name': 'Sala de reuniones / Iluminacion',
                        'description': 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.',
                        'intensity': 55,
                    }
example_object_relay = {
                        'dev_id': 3,
                        'type': 3,
                        'status': 'off',
                        'name': 'Sala de reuniones / Acceso',
                        'description': 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.',
                    }
devices.append(example_object_temp)
devices.append(example_object_dimmer)
devices.append(example_object_relay)
devices = json.dumps(devices)
default_json = json.dumps([{'dev_id':0}])

while 1:
	s.listen(1)
	conn, addr = s.accept()
	print 'Connected by', addr
	while 1:
		data = conn.recv(1024)
		data = json.loads(data)
		print data[0]
		if not data: break
		if data[0]['INTR'] == "SYN":
			text = 'Command \'' + repr(data) + '\', this is a SYN/ACK!'
		elif data[0]['INTR'] == "RQST_ALL":
			text = devices
		else:
			text = default_json
		conn.sendall(text)
	conn.close()