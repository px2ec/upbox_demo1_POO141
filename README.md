upbox
=============

Implementación de domótica modular.

Acerca de...
-------------
En este repositorio se encuentra todo el código fuente necesario para poder implementar un demo de la aplicación **upbox**, creado para fines academicos personales.
También se tienen pretenciones de poder escalar la aplicación a fines domesticos o industriales.

Dependencias
-------------
Para compilar correctamente, se debe tener previamente instalado:

1.  **libjson-glib-1.0-0** y **libjson-glib-1.0-0-dev**
2.  **python-flask**
3.  **libsocket++-dev**
4.  **g++** y **gcc**
5.  **python**

Compilación y ejecución de demonio
-------------
Para compilar el demonio:

1.  cd daemon/
2.  make

Para ejecutar:

1.  ./upboxd

Ejecución de webapp
-------------
Para ejecutar la webapp:

1.  cd webapp/
2.  python webapp.py

Luego, ir al navegador y dirigirse a **localhost:5000**.

-------------

Programa de modulos implementado en Arduino
-------------
Debe tener los perifericos conectados al ordenador que contendrá al demonio.

**Ingresar en la carpeta** *_arduino*.

-------------

Documentación
-------------
Ingresar en la carpeta *documentation*.
