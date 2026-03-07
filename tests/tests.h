#ifndef _TESTS_H_
#define _TESTS_H_

#include "../stack_list/stack_list.h"
#include "../stack_vector/stack_vector.h"
#include "time.h"
#include "sys/time.h"

void    Test1();
void    Test2();
void    Test3();
void    Test4();

double  ListTest1();
double  ListTest2();
double  ListTest3();
double  ListTest4(int elem_cnt);

double  VectTest1();
double  VectTest2();
double  VectTest3();
double  VectTest4(int elem_cnt);

int     GetRandom();
double  GetTime();

#endif