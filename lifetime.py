import numpy as np
import matplotlib.pyplot as plt
lifetime=open("lifetime.txt","r")
dimension=[]
exponente=[]
for line in lifetime:
    data=line.split("\t")
    dimension.append(float(data[0]))
    exponente.append(float(data[1]))
plt.figure(1)
plt.style.use("Solarize_Light2")
plt.plot(dimension,exponente,color="red")
plt.xlabel("Dimensión")
plt.ylabel("Exponente")
plt.legend()
plt.grid()
plt.savefig("lifetime.pdf")
    
