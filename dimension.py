import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from scipy.stats import beta
import math
from funciones import LinearR2
from matplotlib import style
import sys

#Reading of txt files by columns

EFE=sys.argv[1:]
try:
    t=EFE[0]
except:
    t=""
exponentes=[]
dimension=[]
#Column data is saved in arrays
for i in range(2,11):
    colmil_1 = []
    colmil_2 = []
    archivo_datos = open("snake"+str(i)+".txt",'r')
    for line in archivo_datos:
        data = line.split('\t')
        colmil_1.append(float(data[0]))
        colmil_2.append(float(data[1]))
    colmil_1 = np.array(colmil_1).reshape((-1,1))
    colmil_2 = np.array(colmil_2)
    for j in range(len(colmil_2)):
        colmil_1[j]=math.log(colmil_1[j],10)
        colmil_2[j]=math.log(colmil_2[j],10)
    LR_1=LinearR2(colmil_1,colmil_2)
    exponentes.append(float(LR_1[2]))
    dimension.append(i)
#Lifetime
plt.figure(1)
plt.style.use("Solarize_Light2")
plt.xlim(1,1.6)
plt.scatter(dimension,exponentes,linestyle="dashed",linewidth=1, label= "Dimension"+"T="+t, color= "red", marker= "*", s=20)
plt.xlabel('Dimension')
plt.ylabel(r'b')
plt.yscale("log")
plt.legend()
plt.title('Random Path: Exponent')
plt.savefig("exponente"+".png")
#Column data is plotted with points
