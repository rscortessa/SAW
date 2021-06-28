#Here we have the coefficients about linear regression
import math
import numpy as np
from sklearn.linear_model import LinearRegression
def LinearR(col_1, col_2):
    model = LinearRegression()
    model.fit(col_1, col_2)
    model = LinearRegression().fit(col_1, col_2)
    r_sq = model.score(col_1, col_2)
    intercept = model.intercept_
    slope = model.coef_
    COEF = [r_sq , intercept , slope]
    COEF = np.array(COEF)
    return COEF
def Readf(name,rows):
    file=open(name,"r")
    cols=[[] for i in range(0,rows)]
    for line in file:
        data=line.split("\t")
        for i in range(0,rows):
            cols[i].append(float(data[i]))
    return cols


