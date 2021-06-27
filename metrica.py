import numpy as np
import matplotlib.pyplot as plt
import math

archivo_datos = open('metrica.txt','r')

metrica_1 = []
metrica_2 = []
for line in archivo_datos:
    data = line.split('\t')
    metrica_1.append(float(data[0]))
    metrica_2.append(float(data[1]))

metrica_1 = np.array(metrica_1)
metrica_2 = np.array(metrica_2)

Dim = len(metrica_1)

speedup(Dim,0)
eficiencia = []

for x in range (0,Dim):
    speedup [x] = metrica_2[0]/metrica_2[x]
    eficiencia [x] = speedup[x]/metrica_1[x]

speedup = np.array(speedup)
eficiencia = np.array(eficiencia)

plt.plot(metrica_1, speedup, color='red', label='Speedup')
plt.plot(metrica_1, eficiencia, color='blue', label='Efficiency')
plt.title("Efficiency & Speedup")
plt.legend()
plt.grid()
plt.savefig("metrica.pdf")
