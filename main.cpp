#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "solution.h"
#include "input_and_output.h"
#include "other.h"

int main(void)
{
    int ch = 0;

    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    int number_of_solves = 0;

    double x1 = 0.0;
    double x2 = 0.0;

    Greetings();

    while ((ch = getchar()) != '\n')
    {
        ungetc(ch, stdin);

        VerificationOfEnteredData(&a, &b, &c);

        number_of_solves = SolutionsOfEquations(a, b, c, &x1, &x2);

        Conclusion(number_of_solves, x1, x2);

        printf("Введи 3 числа (сначала коэффициент при x^2, потом при x, потом "
                 "свободный) для продолжения или Enter для остановки: ");
    }

    return 0;
}
