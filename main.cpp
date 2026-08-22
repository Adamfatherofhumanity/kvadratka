#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

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

enum EquationErrors
{
    ERROR_EOF = -1,
    ERROR_A = 0,
    ERROR_B = 1,
    ERROR_C = 2,
    NO_ERRORS = 3,
    ERROR_SO_MANY = 4,
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
void InvalidInput(int code_of_error);
void InvalidAnswer(void);
bool CheckString(void);

void Greetings(void);
void PrintEnding(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
int ContinueOrStop(bool * ptr_need_to_continue);

void CheckQuadraticRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
void CheckLinealRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
bool CheckEquationErrors(void);

void SkipString(void);

int main(void)
{
    EquationArgs args = { };

    EquationSolves solves = { };

    Greetings();

    bool need_to_continue = true;

    while (need_to_continue)
    {
        int code_of_error = VerificationOfEnteredData(&args);

        if (code_of_error == NO_ERRORS)
        {
            SolutionsOfEquations(&args, &solves);

            PrintEnding(&args, &solves);

            ContinueOrStop(&need_to_continue);
        }

        else
        {
            InvalidInput(code_of_error);
        }
    }

    return 0;
}

void SolutionsOfEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (ComparisonOfFractalNumbers(ptr_args->a, 0.0) == EQUAL)
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

    double discriminant = ptr_args->b * ptr_args->b - 4 * ptr_args->a * ptr_args->c;

    if (discriminant < 0)
    {
        ptr_solves->number_of_solves = ZERO_SOLVES;
    }

    else if (ComparisonOfFractalNumbers(discriminant, 0.0) == EQUAL)
    {
        ptr_solves->solve1 = (-ptr_args->b) / (2 * ptr_args->a);
        ptr_solves->solve2 = (-ptr_args->b) / (2 * ptr_args->a);
        ptr_solves->number_of_solves = ONE_SOLVE;

        CheckQuadraticRoots(ptr_args, ptr_solves);
    }

    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        ptr_solves->solve1 = (-ptr_args->b - sqrt_discriminant) / (2 * ptr_args->a);
        ptr_solves->solve2 = (-ptr_args->b + sqrt_discriminant) / (2 * ptr_args->a);
        ptr_solves->number_of_solves = TWO_SOLVES;

        CheckQuadraticRoots(ptr_args, ptr_solves);
    }
}

void SolutionsOfLinealEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (ComparisonOfFractalNumbers(ptr_args->b, 0.0) == EQUAL)
    {
        if (ComparisonOfFractalNumbers(ptr_args->c, 0.0) == EQUAL)
        {
            ptr_solves->number_of_solves = INF_SOLVES;
        }

        else
        {
            ptr_solves->number_of_solves = ZERO_SOLVES;
        }
    }

    else
    {
        ptr_solves->solve1 = (-ptr_args->c) / ptr_args->b;
        ptr_solves->number_of_solves = ONE_SOLVE;

        CheckLinealRoots(ptr_args, ptr_solves);
    }
}

int VerificationOfEnteredData(struct EquationArgs * const ptr_args)
{
    assert(ptr_args != NULL);
    assert(CheckEquationErrors());

    int number_of_scanned_args = -1;

    number_of_scanned_args = scanf("%lf %lf %lf", &(ptr_args->a), &(ptr_args->b), &(ptr_args->c));

    if (number_of_scanned_args == 3)
    {
        if (not CheckString())
        {
            number_of_scanned_args += 1;
        }
    }

    return number_of_scanned_args;
}

void PrintEnding(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    printf("У уравнения %.3lf * x^2 + %.3lf * x + %.3lf ", ptr_args->a, ptr_args->b, ptr_args->c);

    switch (ptr_solves->number_of_solves)
    {
        case ZERO_SOLVES:
            printf("нет решений.\n");
            break;

        case ONE_SOLVE:
            printf("одно решение x = %.3lf.\n", ptr_solves->solve1);
            break;

        case TWO_SOLVES:
            printf("два решения x1 = %.3lf и x2 = %.3lf.\n", ptr_solves->solve1, ptr_solves->solve2);
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

void InvalidInput(int code_of_error)
{
    if (code_of_error == ERROR_A || code_of_error == ERROR_B || code_of_error == ERROR_C)
    {
        printf("Аргумент %c введён неверно. Введите данные заново "
               "(сначала коэффициент при x^2, потом при x, потом свободный): ", 97+code_of_error);
        SkipString();
    }

    else if (code_of_error == ERROR_EOF)
    {
        printf("Конец файла.");
        assert(false);
    }

    else if (code_of_error == ERROR_SO_MANY)
    {
        printf("Введены лишние аргументы. Введите данные заново "
               "(сначала коэффициент при x^2, потом при x, потом свободный): ");
        SkipString();
    }

    else
    {
        printf("Произошла непредвиденная ошибка.\n");
        assert(false);
    }
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
    assert(ptr_need_to_continue != NULL);

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

    double value1 = ptr_args->a * ptr_solves->solve1 * ptr_solves->solve1 + ptr_args->b * ptr_solves->solve1 + ptr_args->c;
    double value2 = ptr_args->a * ptr_solves->solve2 * ptr_solves->solve2 + ptr_args->b * ptr_solves->solve2 + ptr_args->c;

    if (ComparisonOfFractalNumbers(value1, 0.0) != EQUAL || ComparisonOfFractalNumbers(value2, 0.0) != EQUAL)
    {
        printf("Произошла ошибка в вычислениях.\n");
        printf("a = %lf, b = %lf, c = %lf, x1 = %lf, x2 = %lf.\n", ptr_args->a, ptr_args->b, ptr_args->c, ptr_solves->solve1, ptr_solves->solve2);
        assert(false);
    }
}

void CheckLinealRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double value = ptr_args->b * ptr_solves->solve1 + ptr_args->c;

    if (ComparisonOfFractalNumbers(value, 0.0) != EQUAL)
    {
        printf("Произошла ошибка в вычислениях.\n");
        printf("b = %lf, c = %lf, x = %lf.\n", ptr_args->b, ptr_args->c, ptr_solves->solve1);
        assert(false);
    }
}

void InvalidAnswer(void)
{
    printf("Принимаются только ответы Y/N (введите Y если да или N если нет): ");
    SkipString();
}

bool CheckEquationErrors(void)
{
    return (ERROR_EOF == -1 && ERROR_A == 0 && ERROR_B == 1 && ERROR_C == 2 && NO_ERRORS == 3 && ERROR_SO_MANY == 4 && UNEXPECTED_ERROR == 5);
}

void SkipString(void)
{
    scanf("%*[^\n]");
    getchar();
}
