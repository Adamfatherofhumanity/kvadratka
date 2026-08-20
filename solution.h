#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

const double EPS = 0.0000000001;

enum Comparison
{
    BIGGER = 1,
    SMALLER = -1,
    EQUAL = 0
};

int ComparisonOfFractalNumbers(double a, double b);

int SolutionsOfEquations(double a, double b, double c, double * px1, double * px2);
int SolutionsOfQuadraticEquations(double a, double b, double c, double * px1, double * px2);
int SolutionsOfLinealEquations(double b, double c, double * px);

#endif
