#!/usr/bin/env python2
# -*- coding: utf-8 -*-

# Copyright (C) 2014, Centro de Robótica
# Universidad Técnica Federico Santa María

#UPDATE `2014-1_equipos` SET `ptje_rondas` = 0.5 * ((`ptje_ronda1` + `ptje_ronda2`) + ABS(`ptje_ronda1` - `ptje_ronda2`));
#UPDATE `2014-1_equipos` SET `ptje_total` = (`ptje_rondas` + `ptje_trabajo` + `ptje_progra`) / 3

from flask import *
from werkzeug import secure_filename
import os
# import oursql as sql
# 
# ## MySQL
# db_host = 'localhost'
# db_port = 3306
# db_user = 'ire'
# db_pass = 'iredosmil14'
# db_name = 'ire'
# 
# ## Verificar que siempre estemos conectado
# db_conn = sql.connect(host=db_host, user=db_user,
#     passwd=db_pass, db=db_name, autoreconnect=True)

# tbl_equipos = '`2014-1_equipos`'
# tbl_participantes = '`2014-1_participantes`'

## Flask
app = Flask('IRE_2014-1')

def http_error_rsp(message, code = 400):
    rsp = make_response(message)
    rsp.status_code = code
    rsp.headers['Access-Control-Allow-Origin'] = '*'

    return rsp

@app.route('/api/puntajes_valpo', methods=['GET'])
def get_ptjes_valpo():
    sortc = 0
    if 'sortc' in request.args:
        sortc = int(request.args['sortc'])
    else:
        sortc = -1

    # cur = db_conn.cursor()
    #     if sortc == 1:
    #         cur.execute('SELECT *  FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad != 2 ORDER BY ptje_progra DESC')
    #     elif sortc == 2:
    #         cur.execute('SELECT *  FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad != 2 ORDER BY ptje_trabajo DESC')
    #     elif sortc == 3:
    #         cur.execute('SELECT *  FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad != 2 ORDER BY ptje_rondas DESC')
    #     elif sortc == -1:
    #         cur.execute('SELECT *  FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad != 2 ORDER BY ptje_ronda1 DESC')
    #     else:
    #         cur.execute('SELECT *  FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad != 2 ORDER BY ptje_total DESC')

    # retlist = list()
    #     for val in cur.fetchall():
    #         retlist.append((val[1],) + val[6:12] + (val[0],))

    # rsp = jsonify(results=retlist)
	rsp = "sdasdads"
    # rsp.headers['Access-Control-Allow-Origin'] = '*'

    return rsp

@app.route('/api/puntajes_conce', methods=['GET'])
def get_ptjes_conce():
    cur = db_conn.cursor()
    cur.execute('SELECT *  FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad = 2')

    retlist = list()
    for val in cur.fetchall():
        retlist.append((val[1],) + val[6:11])

    rsp = jsonify(results=retlist)
    rsp.headers['Access-Control-Allow-Origin'] = '*'

    return rsp

@app.route('/api/equipos_valpo', methods=['GET'])
def get_equipos_valpo():
    cur = db_conn.cursor()
    cur.execute('SELECT id, nombre, participa_r1, participa_r2, turno_competir FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad != 2 ORDER BY turno_competir ASC')

    retlist = list()

    for val in cur.fetchall():
        retlist.append(val)

    cur.close()

    rsp = jsonify(equipos=retlist)
    rsp.headers['Access-Control-Allow-Origin'] = '*'

    return rsp

@app.route('/api/equipos_conce', methods=['GET'])
def get_equipos_conce():
    cur = db_conn.cursor()
    cur.execute('SELECT id, nombre, participa_r1, participa_r2, turno_competir FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad = 2')

    retlist = list()

    for val in cur.fetchall():
        retlist.append(val)

    cur.close()

    rsp = jsonify(equipos=retlist)
    rsp.headers['Access-Control-Allow-Origin'] = '*'

    return rsp

@app.route('/api/shuffle_equipos_valpo', methods=['GET'])
def shuffle_equipos_valpo():
    cur = db_conn.cursor()
    cur.execute('SELECT id FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad != 2 ORDER BY RAND()')

    idlist = list()
    for val in cur.fetchall():
        idlist.append(val[0])

    counter = 1
    for group_id in idlist:
        cur.execute('UPDATE `2014-1_equipos` SET `turno_competir` = ' + str(counter) + ' WHERE `id` = ' + str(group_id))
        counter += 1

    db_conn.commit()
    cur.close()
    return http_error_rsp('OK', 200)

@app.route('/api/shuffle_equipos_conce', methods=['GET'])
def shuffle_equipos_conce():
    cur = db_conn.cursor()
    cur.execute('SELECT id FROM ' + tbl_equipos + ' WHERE acreditado = 1 AND ciudad = 2 ORDER BY RAND()')

    idlist = list()
    for val in cur.fetchall():
        idlist.append(val[0])

    counter = 1
    for group_id in idlist:
        cur.execute('UPDATE `2014-1_equipos` SET `turno_competir` = ' + str(counter) + ' WHERE `id` = ' + str(group_id))
        counter += 1

    db_conn.commit()
    cur.close()
    return http_error_rsp('OK', 200)

@app.route('/api/setear_estado_alto', methods=['GET'])
def set_estado_alto():
    if 'r' not in request.args or 'id' not in request.args:
        http_error_rsp('LOL GTFO', code=403)

    if request.args['r'] == '1':
        columna = 'participa_r1'
    else:
        columna = 'participa_r2'

    group_id = request.args['id']

    cur = db_conn.cursor()
    cur.execute('UPDATE `2014-1_equipos` SET ' + columna + ' = 1 WHERE `id` = ' + str(group_id))

    db_conn.commit()
    cur.close()

    return http_error_rsp('OK', 200)

@app.route('/api/setear_estado_bajo', methods=['GET'])
def set_estado_bajo():
    if 'r' not in request.args or 'id' not in request.args:
        http_error_rsp('LOL GTFO', code=403)

    if request.args['r'] == '1':
        columna = 'participa_r1'
    else:
        columna = 'participa_r2'

    group_id = request.args['id']

    cur = db_conn.cursor()
    cur.execute('UPDATE `2014-1_equipos` SET ' + columna + ' = 0 WHERE `id` = ' + str(group_id))

    db_conn.commit()
    cur.close()

    return http_error_rsp('OK', 200)

@app.route('/api/situacion_equipos', methods=['GET'])
def get_situacion_equipos():
    cur = db_conn.cursor()
    cur.execute('SELECT id, nombre, acreditado, ciudad FROM ' + tbl_equipos + ' ORDER BY ciudad DESC, nombre ASC')

    retlist = list()

    for val in cur.fetchall():
        retlist.append(val)

    cur.close()

    rsp = jsonify(equipos=retlist)
    rsp.headers['Access-Control-Allow-Origin'] = '*'

    return rsp

@app.route('/api/cambiar_situacion', methods=['GET'])
def set_situacion():
    if 'val' not in request.args or 'id' not in request.args:
        http_error_rsp('LOL GTFO', code=403)

    group_id = request.args['id']
    value = request.args['val']

    cur = db_conn.cursor()
    cur.execute('UPDATE `2014-1_equipos` SET `acreditado` = ' + str(value) + ' WHERE `id` = ' + str(group_id))

    db_conn.commit()
    cur.close()
    return http_error_rsp('OK', 200)

@app.route('/consultar', methods=['POST'])
def getTeamInfo():
    if 'equipo' not in request.form:
        return http_error_rsp(u'Debes especificar un grupo\r\n')

    cur = db_conn.cursor()
    cur.execute('SELECT * FROM '+ tbl_equipos +' WHERE `nombre_equipo` = ?',
        (request.form['equipo'],))

    retdict = {
        'equipo': None,
        'integrantes': list(),
    }

    retdict['equipo'] = cur.fetchone()
    cur.close()

    cur = db_conn.cursor()
    cur.execute('SELECT CONCAT(nombres, " ", paterno, " ", materno) FROM '
        + tbl_participantes +' WHERE `equipo` = ?', (retdict['equipo'][1],))
    for mbr in cur.fetchall():
        retdict['integrantes'].append(mbr[0])
    cur.close()

    rsp = jsonify(retdict)
    rsp.headers['Access-Control-Allow-Origin'] = '*'

    return rsp

@app.route('/', methods=['GET'])
def getIndex():
    return

@app.route('/tablaptje', methods=['GET'])
def getScores():
    return

@app.route('/acreditacion', methods=['GET'])
def getCheckIn():
    return

if __name__ == '__main__':
    app.debug = True
    app.run()
