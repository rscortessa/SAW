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
colmil_1,colmil_4  =Readf(name,2)
#We define the teoric curve:
a=2.6060*10**(-3)
b=2.656*10**(-2)
c=6.65*10**(-1)
da=0.00009
db=0.003
dc=0.01
def f(x):
    a=2.6060*10**(-3)
    b=2.656*10**(-2)
    c=6.65*10**(-1)
    da=0.00009
    db=0.003
    dc=0.01
    return a*(x-8)**(c)*np.exp(-b*(x-8))
#Column data is saved in arrays
colmil_1 = np.array(colmil_1).reshape((-1, 1))
colmil_4= np.array(colmil_4)
Dim = len(colmil_1)
#Lifetime
x = np.arange(0,colmil_1[len(colmil_1)-1],1)  
plt.figure(2)
plt.style.use("Solarize_Light2")
#plt.plot(x,f(x), color='red', label='Linear regression')
plt.scatter(colmil_1, colmil_4, label= "Lifetime", color= "green", marker= "*", s=20)
plt.plot(colmil_1, colmil_4, color="green")
plt.xlabel('time (n steps)')
plt.ylabel('$P_{Death}$')
plt.title('Density function of deaths')
#plt.text(75,0.009,"$P_{Death}(n)= (2.60 \pm 0.09)\cdot 10^{-3} (n-8)^{ (6.6\pm 0.1)\cdot 10^{-1}}$",fontsize=8)
#plt.text(80,0.008,r"$\times e^{(2.65\pm 0.03)\cdot 10^{-2}(n-8)}$",fontsize=8)
plt.legend()
plt.grid()
plt.savefig("Lifesnake"+EFE[0]+".png")


