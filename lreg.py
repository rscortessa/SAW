import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from scipy.stats import beta
import math
from matplotlib import style
import sys
import statsmodels.api as sm
from funciones import LinearR
from funciones import LinearR2
from funciones import Readf

EFE=sys.argv[1:]
#Reading of txt files by columns
name="snake"+EFE[0]+".txt"
colmil_1,colmil_2,colmil_3,colmil_4 =Readf(name,4)
est="estadística.txt"
estadistica=Readf(est,3)
dimension=estadistica[0][0]
var=estadistica[1][0]
mu=estadistica[2][0]
#Column data is saved in arrays
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
aux3=np.array(aux3)
    
colmil_4 = np.array(colmil_4)
#Analysis to linear regression

Dim = len(colmil_1)
#Lifetime
x = np.arange(0,colmil_1[len(colmil_1)-1],1)  
plt.figure(1)
plt.style.use("Solarize_Light2")
plt.plot(x,beta.cdf(x,1,4,15,15000), color='red', label='Linear regression')
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
    #print(colmil_1[ii])
    colmil_1[ii]=math.log(colmil_1[ii],10)
    colmil_4[ii]=math.log(colmil_4[ii],10)
    
#LR_1 = LinearR(aux2, aux3)
#b=float(LR_1[1])
#m=float(LR_1[2])
#print(LR_1)
print(LinearR2(aux2, aux3))
#print(result.fit_report()) #print a general scheme about the regression information

#Finally, the linear regression is graphed according to log-log scale
y_12 = (10**LR_1[1])*(x**LR_1[2])
plt.plot(x, y_12, color='blue', label='Linear regression')
plt.text(2,10**(aux2[len(aux2)-1]),r"${\langle R^2 \rangle}_n="+str(round(10**(b),3))+"n^{"+str(round(m,3))+"}$")
plt.legend()
plt.grid()
plt.savefig("linearsnake"+EFE[0]+".pdf")
#Column data is plotted with points
