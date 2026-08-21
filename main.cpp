#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const double EPS = 0.000001;
bool need_to_continue = true;

// TODO: переделать выход из программы на return 0 в main (убрать exit)

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

enum EquationErrors
{
    ERROR_EOF = -1,
    ERROR_A = 0,
    ERROR_B = 1,
    ERROR_C = 2,
    ERROR_SO_MANY = 3,
    NO_ERRORS = 4,
    UNEXPECTED_ERROR = 5
};

struct EquationArgs
{
    double a;
    double b;
    double c;
};

struct EquationSolves
{
    Solves number_of_solves;
    double solve1;
    double solve2;
};

int ComparisonOfFractalNumbers(const double a, const double b);

void SolutionsOfEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);
void SolutionsOfQuadraticEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);
void SolutionsOfLinealEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);

int VerificationOfEnteredData(struct EquationArgs * const ptr_args);
void InvalidInput(char arg);
void InvalidAnswer(void);
bool CheckString(void);

void Greetings(void);
void Conclusion(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
int ContinueOrStop(bool * ptr_need_to_continue);

void CheckQuadraticRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
void CheckLinealRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);

int main(void)
{
    EquationArgs args = { };

    EquationSolves solves = { };

    Greetings();

    while (need_to_continue)
    {
        if (VerificationOfEnteredData(&args) == NO_ERRORS)
        {
            SolutionsOfEquations(&args, &solves);

            Conclusion(&args, &solves);

            ContinueOrStop(&need_to_continue);
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

int VerificationOfEnteredData(struct EquationArgs * const ptr_args)
{
    assert(ptr_args != NULL);
    int number_of_scanned_args = -1;

    number_of_scanned_args = scanf("%lf %lf %lf", &((*ptr_args).a), &((*ptr_args).b), &((*ptr_args).c));

    if (number_of_scanned_args == 3)
    {
        if (not CheckString())
        {
            number_of_scanned_args += 1;
        }
    }

    switch (number_of_scanned_args)
    {
        case -1:
            return ERROR_EOF;

        case 0:
            InvalidInput('a');
            return ERROR_A;

        case 1:
            InvalidInput('b');
            return ERROR_B;

        case 2:
            InvalidInput('c');
            return ERROR_C;

        case 3:
            return NO_ERRORS;

        case 4:
            printf("Введены лишние аргументы. Введите данные заново "
                   "(сначала коэффициент при x^2, потом при x, потом свободный): ");
            scanf("%*[^\n]");
            getchar();
            return ERROR_SO_MANY;

        default:
            printf("Произошла непредвиденная ошибка.\n");
            return UNEXPECTED_ERROR;

    }
}

void Conclusion(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    printf("У уравнения %.3lf * x^2 + %.3lf * x + %.3lf ", (*ptr_args).a, (*ptr_args).b, (*ptr_args).c);

    switch ((*ptr_solves).number_of_solves)
    {
        case ZERO_SOLVES:
            printf("нет решений.\n");
            break;

        case ONE_SOLVE:
            printf("одно решение x = %.3lf.\n", (*ptr_solves).solve1);
            break;

        case TWO_SOLVES:
            printf("два решения x1 = %.3lf и x2 = %.3lf.\n", (*ptr_solves).solve1, (*ptr_solves).solve2);
            break;

        case INF_SOLVES:
            printf("бесконечное количество решений x - любое число.\n");
            break;

        default:
            printf("произошла непредвиденная ситуация.\n");
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
            return false;
        }
    }
}

int ContinueOrStop(bool * ptr_need_to_continue)
{
    int answer= 0;

    printf("Хотите продолжить ввод (введите Y если да или N если нет): ");

    while (1)
    {
        while (isspace(answer = getchar()))
        {
            continue;
        }

        if (answer == 'Y')
        {
            if (CheckString())
            {
                printf("Введи 3 числа (сначала коэффициент при x^2, потом при x, потом свободный): ");
                return 0;
            }
        }

        else if (answer == 'N')
        {
            if (CheckString())
            {
                printf("Спасибо, что пользовались моей программой.");
                *ptr_need_to_continue = false;
                return 0;
            }
        }

        InvalidAnswer();
    }
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

void InvalidAnswer(void)
{
    printf("Принимаются только ответы Y/N (введите Y если да или N если нет): ");
    scanf("%*[^\n]");
    getchar();
}
