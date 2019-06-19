#lo que Ud. tiene que programar
from gravitacion import *

#para dibujar
import time
import psutil
import matplotlib.pyplot as pt

pt.rcParams['animation.html'] = 'jshtml'
fig = pt.figure()
ax = fig.add_subplot(111)

#crea la simulacion
r_disco=3e12
s=sim(1.988e30, 1.898e27,  7.7857e11, 500, r_disco)
fig.show()

i = 0
#simula 4600 dias
while i < 100:
	r=s.run(46)

	#extrae las posiciones de los cuerpos
	xx, yy = zip(*[[c.x, c.y] for c in r])

	#dibuja
	pt.plot(xx[0],yy[0],'r.')
	pt.plot(xx[2:],yy[2:],'b.')
	pt.plot(xx[1],yy[1],'g.')
	pt.xlim(-r_disco,r_disco)
	pt.ylim(-r_disco,r_disco)
	fig.canvas.draw()
	time.sleep(0.01)
	fig.clf()
	i += 1
pt.close()