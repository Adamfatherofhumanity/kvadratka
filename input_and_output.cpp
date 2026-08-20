#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "input_and_output.h"
#include "other.h"

int VerificationOfEnteredData(double * pa, double * pb, double *pc)
{
    assert(pa != NULL);
    assert(pb != NULL);
    assert(pc != NULL);

    while (1)
    {
        while (scanf("%lf %lf %lf", pa, pb, pc) != 3)
        {
            InvalidInput();
        }

        if (CheckString())
        {
            return 0;
        }
    }
}

void Conclusion(int number_of_solves, double x1, double x2)
{
    switch (number_of_solves)
    {
    case ZERO_SOLVES:
        printf("У уравнения нет решений.\n");
        break;

    case ONE_SOLVE:
        printf("У уравнения 1 решение x = %.3lf.\n", x1);
        break;

    case TWO_SOLVES:
        printf("У уравнения 2 решения x1 = %.3lf и x2 = %.3lf.\n", x1, x2);
        break;

    case INF_SOLVES:
        printf("У уравнения бесконечное количество решений x - любое число.\n");
        break;

    default:
        printf("Произошла непредвиденная ситуация.\n");
        break;
    }
}

void Greetings(void)
{
    printf("Приветствую, пользователь.\nЯ программа, умеющая решать квадратные уравнения."
             "\nВведи 3 числа (сначала коэффициент при x^2, потом при x, потом свободный): ");
}

void InvalidInput(void)
{
    printf("Данные введены неверно. Введите данные заново "
           "(сначала коэффициент при x^2, потом при x, потом свободный): ");
    scanf("%*[^\n]");
    getchar();
}

int CheckString(void)
{
    int ch = 0;

    while (1)
    {
        if (isspace(ch = getchar()))
        {
            if (ch == '\n')
            {
                return 1;
            }
        }

        else
        {
            InvalidInput();
            return 0;
        }
    }
}
