import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
import math

#Reading of txt files by columns
archivo_datos = open('snake.txt','r')

colmil_1 = []
colmil_2 = []
colmil_3 = []
colmil_4 = []
#Column data is saved in arrays
for line in archivo_datos:
    data = line.split('\t')
    colmil_1.append(float(data[0]))
    colmil_2.append(float(data[1]))
    colmil_3.append(float(data[2]))
    colmil_4.append(float(data[3]))

colmil_1 = np.array(colmil_1).reshape((-1, 1))
colmil_2 = np.array(colmil_2)
colmil_3 = np.array(colmil_3)
colmil_4 = np.array(colmil_4)

#Column data is plotted with points
plt.scatter(colmil_1, colmil_2, label= "Expected value", color= "green", marker= "+", s=30)
plt.scatter(colmil_1, colmil_4, label= "Expected radius", color= "red", marker= "*", s=30)
plt.xlabel('n steps')
plt.xscale("log")
#plt.semilogx(base=5)
plt.ylabel('<R²>')
plt.yscale("log")
plt.title('Random Path: Linear Regression')

#Analysis to linear regression
Dim = len(colmil_1)
#Array data is re-escaled to log-log scale
for jj in range(0, Dim):
    colmil_1[jj]=math.log(colmil_1[jj],10)
    colmil_2[jj]=math.log(colmil_2[jj],10)
    colmil_4[jj]=math.log(colmil_4[jj],10)


#Here we have the coefficients about linear regression
model = LinearRegression()
model.fit(colmil_1, colmil_2)
model = LinearRegression().fit(colmil_1, colmil_2)
r_sq_12 = model.score(colmil_1, colmil_2)
intercept_12 = model.intercept_
slope_12 = model.coef_

model = LinearRegression()
model.fit(colmil_1, colmil_4)
model = LinearRegression().fit(colmil_1, colmil_4)
r_sq_14 = model.score(colmil_1, colmil_4)
intercept_14 = model.intercept_
slope_14 = model.coef_
#print('coefficient of determination:', r_sq)
#print('slope:', slope)
#print('intercept:', intercept)

#Finally, the linear regression is graphed...
x = np.arange(2, 1000, 0.1)
#according to log-log scale
y_12 = (10**intercept_12)*(x**slope_12)
y_14 = (10**intercept_14)*(x**slope_14)

plt.plot(x, y_12, color='blue', label='Linear regression')
plt.plot(x, y_12, color='orange', label='Linear regression')
plt.legend()
plt.grid()
plt.savefig('linearsnake.pdf')
#plt.show()
