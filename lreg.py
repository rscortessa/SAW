#import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
import math

archivo_datos = open('snake100.txt','r')

col100_1 = []
col100_2 = []
for line in archivo_datos:
    data = line.split('\t')
    col100_1.append(float(data[0]))
    col100_2.append(float(data[1]))

col100_1 = np.array(col100_1)
col100_2 = np.array(col100_2)


archivo_datos = open('snakemil.txt','r')

colmil_1 = []
colmil_2 = []
for line in archivo_datos:
    data = line.split('\t')
    colmil_1.append(float(data[0]))
    colmil_2.append(float(data[1]))

colmil_1 = np.array(colmil_1).reshape((-1, 1))
colmil_2 = np.array(colmil_2)

D100 = len(col100_1)
Dmil = len(colmil_1)

for ii in range(0, D100):
    col100_1[ii]=math.log(col100_1[ii],5)
    col100_2[ii]=math.log(col100_2[ii],10)

for jj in range(0, Dmil):
    colmil_1[jj]=math.log(colmil_1[jj],5)
    colmil_2[jj]=math.log(colmil_2[jj],10)

#print(f"{col100_1}")

model = LinearRegression()
model.fit(colmil_1, colmil_2)
model = LinearRegression().fit(colmil_1, colmil_2)
r_sq = model.score(colmil_1, colmil_2)
intercept = model.intercept_
slope = model.coef_

#print('coefficient of determination:', r_sq)
#print('slope:', slope)
#print('intercept:', intercept)


#y= slope*x+intercept

plt.scatter(colmil_1, colmil_2, label= "Average", color= "green", marker= "+", s=30)
plt.xlabel('n steps')
plt.ylabel('<R²>')
plt.title('Random Path: Linear Regression')
#plot.plot(x,y)
plt.show()

# Visualize
#plt.xlabel('N steps', fontsize=s)
#plt.ylabel('<R²>', fontsize=s)
#plt.scatter(X, Y)
#plt.plot(X, Y, color='red')
#plt.show()
