#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "solution.h"
#include "other.h"

int SolutionsOfEquations(double a, double b, double c, double * px1, double * px2)
{
    assert(px1 != NULL);
    assert(px2 != NULL);
    assert(px1 != px2);

    if (ComparisonOfFractalNumbers(a, 0.0) == EQUAL)
    {
        return SolutionsOfLinealEquations(b, c, px1);
    }

    else
    {
        return SolutionsOfQuadraticEquations(a, b, c, px1, px2);
    }
}

int ComparisonOfFractalNumbers(double a, double b)
{
    if (a - b > EPS)
    {
        return BIGGER;
    }

    else if (a - b < -EPS)
    {
        return SMALLER;
    }

    else
    {
        return EQUAL;
    }
}

int SolutionsOfQuadraticEquations(double a, double b, double c, double * px1, double * px2)
{
    assert(px1 != NULL);
    assert(px2 != NULL);
    assert(px1 != px2);

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return ZERO_SOLVES;
    }

    else if (ComparisonOfFractalNumbers(discriminant, 0.0) == EQUAL)
    {
        *px1 = (-b) / (2 * a);
        *px2 = (-b) / (2 * a);

        return ONE_SOLVE;
    }

    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        *px1 = (-b - sqrt_discriminant) / (2 * a);
        *px2 = (-b + sqrt_discriminant) / (2 * a);

        return TWO_SOLVES;
    }
}

int SolutionsOfLinealEquations(double b, double c, double * px)
{
    assert(px != NULL);

    if (ComparisonOfFractalNumbers(b, 0.0) == EQUAL)
    {
        if (ComparisonOfFractalNumbers(c, 0.0) == EQUAL)
        {
            return INF_SOLVES;
        }

        else
        {
            return ZERO_SOLVES;
        }
    }

    else
    {
        *px = (-c) / b;

        return ONE_SOLVE;
    }
}
