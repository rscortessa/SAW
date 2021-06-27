import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from scipy.stats import beta
import math
from matplotlib import style
import sys
EFE=sys.argv[1:]
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




#Reading of txt files by columns
archivo_datos = open("snake"+EFE[0]+".txt",'r')
estadistica=open("estadística.txt","r")
var=0
mu=0
for line in estadistica:
    data=line.split("\t")
    var=float(data[2])
    mu=float(data[1])
A=mu*mu/var
B=mu/var
var=var-mu**2
colmil_1 = []
colmil_2 = []
colmil_3 = []
colmil_4 = []
aux=[]
aux1=[]
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
aux=[]
aux1=[]
aux2=[]
aux3=[]
for x in np.array(colmil_3):
    if (x-0.01)>0:
        aux.append(x)
for x in range(0,len(colmil_3)):
    if (colmil_3[x]<0.8):
        aux2.append(colmil_1[x])
        aux3.append(colmil_2[x])
aux2=np.array(aux2).reshape((-1,1))
for x in range(len(colmil_3)-len(aux)+2,len(colmil_3)+2):
    aux1.append(x)
aux1=np.array(aux1).reshape((-1,1))
    
colmil_4 = np.array(colmil_4)
#Analysis to linear regression

Dim = len(colmil_1)
#Lifetime
x = np.arange(0,colmil_1[len(colmil_1)-1],1)  
plt.figure(1)
plt.style.use("Solarize_Light2")
plt.plot(x,beta.cdf(x,1,4,15,272), color='red', label='Linear regression')
plt.scatter(colmil_1, colmil_3, label= "Lifetime", color= "green", marker= "*", s=20)
plt.xlabel('time (n steps)')
plt.ylabel('% (Deaths/total)')
plt.title('Lifetime')
plt.text(150,0.8,r"$\langle T \rangle ="+str(beta.mean(1,4)*(272)+15)+"(2)[n]$",fontsize=12)
plt.text(150,0.7,r"$F_{X} =I_{x}(1,4)$",fontsize=12)
plt.text(150,0.6,r"$15\leq x\geq 272$",fontsize=12)
plt.legend()
plt.grid()
plt.savefig("Lifesnake"+EFE[0]+".pdf")

#Column data is plotted with points
plt.figure(2)
plt.style.use("Solarize_Light2")
plt.scatter(aux2, aux3, label= "Expected value", color= "green", marker= "+", s=20)
plt.scatter(colmil_1, colmil_4, label= "Expected radius", color= "red", marker= "*", s=20)
plt.xlabel('n steps')
plt.xscale("log")
#plt.semilogx(base=5)
plt.ylabel(r'$\langle R^2 \rangle$')
plt.yscale("log")
plt.legend()
plt.title('Random Path: Linear Regression')


#Array data is re-escaled to log-log scale
for jj in range(0,len(aux3)):
    aux3[jj]=math.log(aux3[jj],10)
    aux2[jj]=math.log(aux2[jj],10)
for ii in range(0,Dim):
    print(colmil_1[ii])
    colmil_1[ii]=math.log(colmil_1[ii],10)
    colmil_4[ii]=math.log(colmil_4[ii],10)
    
LR_1 = LinearR(aux2, aux3)
b=float(LR_1[1])
m=float(LR_1[2])
print(LR_1)
#Finally, the linear regression is graphed...

#... according to log-log scale
y_12 = (10**LR_1[1])*(x**LR_1[2])
plt.plot(x, y_12, color='green', label='Linear regression')
plt.text(2,10**(aux2[len(aux2)-1]),r"${\langle R^2 \rangle}_n="+str(round(np.exp(b),3))+"e^{"+str(round(m,3))+"n}$")
plt.legend()
plt.grid()
plt.savefig("linearsnake"+EFE[0]+".pdf")
#Column data is plotted with points
