#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const double EPS = 0.000001;

enum Comparison
{
    BIGGER = 1,
    SMALLER = -1,
    EQUAL = 0
};

enum Solves
{
    INF_SOLVES = 3,
    ZERO_SOLVES = 0,
    ONE_SOLVE = 1,
    TWO_SOLVES = 2
};

struct EquationArgs
{
    double a;
    double b;
    double c;
};

struct EquationSolves
{
    int number_of_solves;
    double solve1;
    double solve2;
};

int ComparisonOfFractalNumbers(const double a, const double b);

void SolutionsOfEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);
void SolutionsOfQuadraticEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);
void SolutionsOfLinealEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);

bool VerificationOfA(struct EquationArgs * const ptr_args);
bool VerificationOfB(struct EquationArgs * const ptr_args);
bool VerificationOfC(struct EquationArgs * const ptr_args);
void InvalidInput(char arg);
bool CheckString(void);

void Greetings(void);
void Conclusion(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
void ContinueOrStop(void);

void CheckQuadraticRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
void CheckLinealRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);

int main(void)
{
    int ch = 0;

    EquationArgs args = { };

    EquationSolves solves = { };

    Greetings();

    while ((ch = getchar()) != '\n')
    {
        ungetc(ch, stdin);

        if (VerificationOfA(&args))
        {
            SolutionsOfEquations(&args, &solves);

            Conclusion(&args, &solves);

            ContinueOrStop();
        }
    }

    return 0;
}

void SolutionsOfEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (ComparisonOfFractalNumbers((*ptr_args).a, 0.0) == EQUAL)
    {
        SolutionsOfLinealEquations(ptr_args, ptr_solves);
    }

    else
    {
        SolutionsOfQuadraticEquations(ptr_args, ptr_solves);
    }
}

int ComparisonOfFractalNumbers(const double a, const double b)
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

void SolutionsOfQuadraticEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double discriminant = (*ptr_args).b * (*ptr_args).b - 4 * (*ptr_args).a * (*ptr_args).c;

    if (discriminant < 0)
    {
        (*ptr_solves).number_of_solves = ZERO_SOLVES;
    }

    else if (ComparisonOfFractalNumbers(discriminant, 0.0) == EQUAL)
    {
        (*ptr_solves).solve1 = (-(*ptr_args).b) / (2 * (*ptr_args).a);
        (*ptr_solves).solve2 = (-(*ptr_args).b) / (2 * (*ptr_args).a);
        (*ptr_solves).number_of_solves = ONE_SOLVE;

        CheckQuadraticRoots(ptr_args, ptr_solves);
    }

    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        (*ptr_solves).solve1 = (-(*ptr_args).b - sqrt_discriminant) / (2 * (*ptr_args).a);
        (*ptr_solves).solve2 = (-(*ptr_args).b + sqrt_discriminant) / (2 * (*ptr_args).a);
        (*ptr_solves).number_of_solves = TWO_SOLVES;

        CheckQuadraticRoots(ptr_args, ptr_solves);
    }
}

void SolutionsOfLinealEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (ComparisonOfFractalNumbers((*ptr_args).b, 0.0) == EQUAL)
    {
        if (ComparisonOfFractalNumbers((*ptr_args).c, 0.0) == EQUAL)
        {
            (*ptr_solves).number_of_solves = INF_SOLVES;
        }

        else
        {
            (*ptr_solves).number_of_solves = ZERO_SOLVES;
        }
    }

    else
    {
        (*ptr_solves).solve1 = (-(*ptr_args).c) / (*ptr_args).b;
        (*ptr_solves).number_of_solves = ONE_SOLVE;

        CheckLinealRoots(ptr_args, ptr_solves);
    }
}

bool VerificationOfA(struct EquationArgs * const ptr_args)
{
    assert(ptr_args != NULL);

    if (scanf("%lf", &((*ptr_args).a)) != 1)
    {
        InvalidInput('a');
        return false;
    }

    else
    {
        return VerificationOfB(ptr_args);
    }
}

bool VerificationOfB(struct EquationArgs * const ptr_args)
{
    assert(ptr_args != NULL);

    if (scanf("%lf", &((*ptr_args).b)) != 1)
    {
        InvalidInput('b');
        return false;
    }

    else
    {
        return VerificationOfC(ptr_args);
    }
}

bool VerificationOfC(struct EquationArgs * const ptr_args)
{
    assert(ptr_args != NULL);

    if (scanf("%lf", &((*ptr_args).c)) != 1)
    {
        InvalidInput('c');
        return false;
    }

    else
    {
        return CheckString();
    }
}

void Conclusion(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    switch ((*ptr_solves).number_of_solves)
    {
        case ZERO_SOLVES:
            printf("У уравнения %.3lf * x^2 + %.3lf * x + %.3lf нет решений.\n", (*ptr_args).a, (*ptr_args).b, (*ptr_args).c);
            break;

        case ONE_SOLVE:
            printf("У уравнения %.3lf * x^2 + %.3lf * x + %.3lf одно решение x = %.3lf.\n", (*ptr_args).a, (*ptr_args).b, (*ptr_args).c, (*ptr_solves).solve1);
            break;

        case TWO_SOLVES:
            printf("У уравнения %.3lf * x^2 + %.3lf * x + %.3lf два решения x1 = %.3lf и x2 = %.3lf.\n", (*ptr_args).a, (*ptr_args).b, (*ptr_args).c, (*ptr_solves).solve1, (*ptr_solves).solve2);
            break;

        case INF_SOLVES:
            printf("У уравнения %.3lf * x^2 + %.3lf * x + %.3lf бесконечное количество решений x - любое число.\n", (*ptr_args).a, (*ptr_args).b, (*ptr_args).c);
            break;

        default:
            printf("Произошла непредвиденная ситуация.\n");
            break;
    }
}

void Greetings(void)
{
    printf("Приветствую, пользователь.\nЯ программа, умеющая решать квадратные уравнения.\n"
           "Введи 3 числа (сначала коэффициент при x^2, потом при x, потом свободный): ");
}

void InvalidInput(char arg)
{
    printf("Аргумент %c введён неверно. Введите данные заново "
           "(сначала коэффициент при x^2, потом при x, потом свободный): ", arg);
    scanf("%*[^\n]");
    getchar();
}

bool CheckString(void)
{
    int ch = 0;

    while (1)
    {
        if (isspace(ch = getchar()))
        {
            if (ch == '\n')
            {
                return true;
            }
        }

        else
        {
            printf("Введены лишние аргументы. Введите данные заново "
                   "(сначала коэффициент при x^2, потом при x, потом свободный):");
            scanf("%*[^\n]");
            getchar();
            return false;
        }
    }
}

void ContinueOrStop(void)
{
    printf("Введи 3 числа (сначала коэффициент при x^2, потом при x, потом "
           "свободный) для продолжения или Enter для остановки: ");
}

void CheckQuadraticRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double value1 = (*ptr_args).a * (*ptr_solves).solve1 * (*ptr_solves).solve1 + (*ptr_args).b * (*ptr_solves).solve1 + (*ptr_args).c;
    double value2 = (*ptr_args).a * (*ptr_solves).solve2 * (*ptr_solves).solve2 + (*ptr_args).b * (*ptr_solves).solve2 + (*ptr_args).c;

    if (ComparisonOfFractalNumbers(value1, 0.0) != EQUAL || ComparisonOfFractalNumbers(value2, 0.0) != EQUAL)
    {
        printf("Произошла ошибка в вычислениях.\n");
        exit(EXIT_FAILURE);
    }
}

void CheckLinealRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double value = (*ptr_args).b * (*ptr_solves).solve1 + (*ptr_args).c;

    if (ComparisonOfFractalNumbers(value, 0.0) != EQUAL)
    {
        printf("Произошла ошибка в вычислениях.\n");
        exit(EXIT_FAILURE);
    }
}
