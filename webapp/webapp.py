#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import flask
import flask.views
import DasSocket as sock
import json

app = flask.Flask(__name__)
app.secret_key = '24dcf6c28f5b6bcf69ecb279bd616459f5ac4ccf'

class Devices():
	"""docstring for Devices"""
	def __init__(self):
		self.devices = list()	
	def set (self, devices):
		self.devices = devices
	def get (self):
		return self.devices

devices_list = Devices()

example_object_temp = {
						'dev_id': 1,
						'type': 1,
						'type_desc': u'Sensor Temp',
						'status': True,
						'name': u'Sala de reuniones / Temperatura',
						'description': u'Lorem ipsum dolor sit amet, consectetur adipiscing elit.',
						'temperature': 18,
					}
example_object_dimmer = {
						'dev_id': 2,
						'type': 2,
						'type_desc': u'Dimmer',
						'status': True,
						'name': u'Sala de reuniones / Iluminacion',
						'description': u'Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.',
						'intensity': 55,
					}
example_object_relay = {
						'dev_id': 3,
						'type': 3,
						'type_desc': u'Relay',
						'status': True,
						'name': u'Sala de reuniones / Acceso',
						'description': u'Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.',
					}
example_object_temp2 = {
						'dev_id': 4,
						'type': 1,
						'type_desc': u'Sensor Temp',
						'status': False,
						'name': u'Oficina / Temperatura',
						'description': u'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.',
						'temperature': -40,
					}
example_object_dimmer2 = {
						'dev_id': 5,
						'type': 2,
						'type_desc': u'Dimmer',
						'status': False,
						'name': u'Oficina / Iluminacion',
						'description': u'Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo.',
						'intensity': 55,
					}
example_object_relay2 = {
						'dev_id': 6,
						'type': 3,
						'type_desc': u'Relay',
						'status': False,
						'name': u'Oficina / Acceso',
						'description': u'Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.',
					}
# devices.append(example_object_temp)
# devices.append(example_object_dimmer)
# devices.append(example_object_relay)
# devices.append(example_object_temp2)
# devices.append(example_object_dimmer2)
# devices.append(example_object_relay2)

class Index(flask.views.MethodView):
	def get(self):
		# socket stuff
		socket.connect()
		data = socket.get_peripherals_of_module()
		data = json.loads(data)
		data = data['DEV_LIST']
		devices_list.set(data)
		objpage = dict()
		objpage['title'] = 'upBox'
		objpage['header'] = 'Home'
		objpage['subheader'] = 'Dispositivos detectados'
		# return flask.render_template('index.html', obj=objpage, devices=devices)
		return flask.render_template('index.html', obj=objpage, devices=devices_list.get())

class Close(flask.views.MethodView):
	"""Cierra conexion al modulo"""
	def get(self):
		socket.connect()
		# print socket.query(1, "OFFLED")
		return socket.close()

class DeviceAPI(flask.views.MethodView):
	def get(self, dev_id):
		objpage = {'title': 'upBox',
				   'header': 'Dispositivo',
				   'subheader': ''}
		dev_info = {'status': None}

		if dev_id is None:
			# Show all devices
			return flask.redirect(flask.url_for('index'))
		devices = devices_list.get()
		
		for sel in xrange(len(devices)):
			# Show a specific device
			print 'post_position:', sel
			if devices[sel]['dev_id'] == dev_id:
				print 'the device:', devices[sel]
				objpage['subheader'] = devices[sel]['name']
				#return flask.render_template('device.html', obj=objpage, dev_info=devices[sel])
				dev_info['dev_id'] = devices[sel]['dev_id']
				dev_info['status'] = devices[sel]['status']
				dev_info['description'] = devices[sel]['description']
				#print devices[sel]
				if devices[sel]['type'] == 1:
					dev_info['temperature'] = devices[sel]['temperature']
					return flask.render_template('device_temp.html', obj=objpage, dev_info=dev_info)
				elif devices[sel]['type'] == 2:
					dev_info['intensity'] = devices[sel]['intensity']
					return flask.render_template('device_dimmer.html', obj=objpage, dev_info=dev_info)
				elif devices[sel]['type'] == 3:
					return flask.render_template('device_relay.html', obj=objpage, dev_info=dev_info)
				break

		return flask.redirect(flask.url_for('index'))

	def post(self, dev_id):
		devices = devices_list.get()
		if dev_id is None:
			# Show all devices
			return flask.redirect(flask.url_for('index'))
		pos = get_device_pos(dev_id)
		print 'post_position:', pos
		if pos == None:
			return http_error_rsp('Error :(', 400)

		if 'status' in flask.request.form:
			new_value = flask.request.form['status']
			if new_value == 'True':
				devices[pos]['status'] = True
				if devices[pos]['type'] == 2:
					socket.query(devices[pos]['dev_id'], "ONLED", '')
				else:
					socket.query(devices[pos]['dev_id'], "ONACT", '')
			elif new_value == 'False':
				devices[pos]['status'] = False
				if devices[pos]['type'] == 2:
					socket.query(devices[pos]['dev_id'], "OFFLED", '')
				else:
					socket.query(devices[pos]['dev_id'], "OFFACT", '')
			else:
				return http_error_rsp('Error :(', 400)

		if 'intensity' in flask.request.form and devices[pos]['type'] == 2:
			new_value = flask.request.form['intensity']
			print 'Intensidad:', new_value
			try:
				devices[pos]['intensity'] = int(new_value)
				socket.query(devices[pos]['dev_id'], "SET_INTENSITY", new_value)
			except:
				return http_error_rsp('Error :(', 400)

		return http_error_rsp('OK', 200)

def http_error_rsp(message, code = 400):
	rsp = flask.make_response(message)
	rsp.status_code = code
	rsp.headers['Access-Control-Allow-Origin'] = '*'

	return rsp

def get_device_pos(dev_id):
	devices = devices_list.get()
	for sel in xrange(len(devices)):
		if devices[sel]['dev_id'] == dev_id:
			return sel
	return None

app.add_url_rule('/',
				 view_func=Index.as_view('index'),
				 methods=['GET'])

app.add_url_rule('/devices/',
				 defaults={'dev_id': None},
				 view_func=DeviceAPI.as_view('devices'),
				 methods=['GET',])

app.add_url_rule('/devices/<int:dev_id>',
				 view_func=DeviceAPI.as_view('device_api'),
				 methods=['GET', 'POST'])

app.debug = True
if __name__ == '__main__':
	socket = sock.DasSocket(host = '127.0.0.1', port = 5556)
	# socket = sock.DasSocket()
	app.run(host='0.0.0.0')