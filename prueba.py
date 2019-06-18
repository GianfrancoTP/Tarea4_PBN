#lo que Ud. tiene que programar
from gravitacion import sim

#para dibujar
import matplotlib.pyplot as pt

#crea la simulacion
r_disco=3e12
s=sim(1.988e30, 1.898e27,  7.7857e11, 5000, r_disco)

#simula 4600 dias
r=s.run(1)

#extrae las posiciones de los cuerpos
xx, yy = zip(*[[c.x, c.y] for c in r])
print(xx)
print(yy)

#dibuja
pt.figure()
pt.plot(xx,yy,'b.')
pt.xlim(-r_disco,r_disco)
pt.ylim(-r_disco,r_disco)
pt.show()
