#ifndef _RANDOM_H_
#define _RANDOM_H_
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <cmath>
int* random_step(int dimension, int *r);
double final_position(int dimension, int total_steps);
double average(int dimension, int total_steps, int walks);
#endif
