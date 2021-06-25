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

#Lifetime
plt.figure(1)
plt.scatter(colmil_1, colmil_3, label= "Lifetime", color= "green", marker= "+", s=20)
plt.xlabel('time (n steps)')
plt.ylabel('% (alive/total)')
plt.title('Lifetime')
plt.grid()
plt.savefig('Lifesnake.pdf')

#Column data is plotted with points
plt.figure(2)
plt.scatter(colmil_1, colmil_2, label= "Expected value", color= "green", marker= "+", s=20)
plt.scatter(colmil_1, colmil_4, label= "Expected radius", color= "red", marker= "*", s=20)
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
def LinearR(col_1, col_2):
    model = LinearRegression()
    model.fit(col_1, col_2)
    model = LinearRegression().fit(col_1, col_2)
    r_sq = model.score(colmil_1, colmil_2)
    intercept = model.intercept_
    slope = model.coef_
    COEF = [r_sq , intercept , slope]
    COEF = np.array(COEF)
    return COEF


LR_1 = LinearR(colmil_1, colmil_2)
LR_2 = LinearR(colmil_1, colmil_4)

print(LR_1)
#Finally, the linear regression is graphed...
x = np.arange(2, 200, 0.1)
#... according to log-log scale
y_12 = (10**LR_1[1])*(x**LR_1[2])
y_14 = (10**LR_2[1])*(x**LR_2[2])

plt.plot(x, y_12, color='yellow', label='Linear regression')
#plt.plot(x, y_14, color='red', label='Linear regression')
plt.legend()
plt.grid()
plt.savefig('linearsnake.pdf')
