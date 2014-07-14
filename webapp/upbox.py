#!/usr/bin/python

import socket as sckt
import json
import flask, flask.views
from flask import jsonify
app = flask.Flask(__name__)

#necesario para usar POST
app.secret_key = "basura"

class DasSocket:
	"""Clase para manejo de Sockets"""
	# Constructor del Socket
	# los parametros son los correspondientes para conectarse al modulo
	def __init__(self, host = '',port = 6000):	
		self.h = host
		self.p = port
		#Flag que indica si Socket esta habilitado
		self.up = 0
	
	# metodo para conectar al modulo
	def connect(self):
		if self.up == 0:
			self.s = sckt.socket(sckt.AF_INET, sckt.SOCK_STREAM)
			self.s.connect((self.h, self.p))
			# en fase produccion borrar lineas
			# data = [ { 'INTR':'SYN'} ] # to-do: implementar instruccion SYN en los modulos
			# data = json.dumps(data[0])
			# self.s.sendall(data)
			# self.data = repr(self.s.recv(1024))
			# print 'Socket opened on', self.h, ' (', self.p,')'
			# print 'It says', self.data
			# hasta aqui
			self.up = 1
		else:
			print 'Socket already opened'
	
	# cerrar conexion Socket
	def close(self):
		self.up = 0
		return "Socket closed"
	
	# retorna los valores de todos los perifericos del modulo
	def get_peripherals_of_module(self):
		getall = [ { 'INTR':'RQST_ALL'} ]
		getall = json.dumps(getall[0])
		print "Sending query"
		print self.s.sendall(getall)
		data = self.s.recv(4096) # los modulos deben retornar aca un listado de sus dispositivos asociados
		print data
		return data
		
	# retorna un valor o JSON del metodo consultado al modulo
	# to-do: implementar 'PARAM' en los modulos
	def query(self, ident, method):
		# q = [ { 'dev_id':repr(ident), 'INTR':method, 'PARAM': arguments } ]
		q = [ { 'dev_id':ident, 'INTR':method } ]
		q = json.dumps(q[0])
		self.s.sendall(q)
		return self.s.recv(1024)

class View(flask.views.MethodView):
	"""Primera prueba"""
	def get(self):
		print "Get"
		#reviso si tengo conexion
		socket.connect()
		#le pido al modulo los datos de sus perifericos, para probar conexion
		data = socket.get_peripherals_of_module()
		print data
		return flask.render_template('index.html')

class Close(flask.views.MethodView):
	"""Cierra conexion al modulo"""
	def get(self):
		socket.connect()
		print socket.query(1, "OFFLED")
		return socket.close()
		
class Cosas(flask.views.MethodView):
	"""Ejemplo de uso del socket"""

	def get(self):
		print "Get all peripherals"
		#reviso si tengo conexion
		socket.connect()
		#le pido al modulo los datos de sus perifericos
		data = socket.get_peripherals_of_module()
		#json FTW
		data = json.loads(data)
		print repr(data)
		#saco el primer dispositivo, ya que no se como trabajar un listado en html (Ahora es tu turno Felipe :D)
		data = data['DEV_LIST'][0]
		flask.flash(data['dev_id'])
		flask.flash(data['type'])
		flask.flash(data['status'])
		flask.flash(data['name'])
		flask.flash(data['description'])
		return flask.render_template('index.html')
		
app.add_url_rule('/', view_func=View.as_view('main'), methods=['GET', 'POST'])
app.add_url_rule('/cosas', view_func=Cosas.as_view('cosas'), methods=['GET', 'POST'])
app.add_url_rule('/closeSocket', view_func=Close.as_view('close'), methods=['GET'])

app.debug = True
socket = DasSocket(host = '10.150.15.138', port = 5556)
app.run(host='0.0.0.0')