#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

const double EPS = 1e-6;

const int MINIMUM_ARGS_FOR_TEST = 2;
const int NUMBER_OF_SPECIAL_TESTS = 8;
const double ACCURACY = 1000;

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
void InvalidInput(const int code_of_error, bool * ptr_need_to_continue);
void InvalidAnswer(void);
bool CheckString(void);

void Greetings(void);
void PrintEnding(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
int ContinueOrStop(bool * ptr_need_to_continue);

void CheckQuadraticRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
void CheckLinealRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
bool CheckEquationErrors(void);

void SkipString(void);

int StringToNumber(const char * string);

void RunTests(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves, const int number_of_random_tests, const bool visible_args);
void RunSpecialTests(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves, const bool visible_args);
void RunRandomTests(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves, const int number_of_random_tests, const bool visible_args);

void TestModeGreetings(void);
void InvalidCommand(void);
void PrintArgs(const struct EquationArgs * const ptr_args, const bool visible_args);

void ClientProgram(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);
void TestingProgram(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves, const int argc, const char * const argv[]);

int main(int argc, char * argv[])
{
    EquationArgs args = { };
    EquationSolves solves = { };

    if (argc >= MINIMUM_ARGS_FOR_TEST && strcmp(argv[MINIMUM_ARGS_FOR_TEST-1], "test") == 0)
    {
        TestingProgram(&args, &solves, argc, argv);
    }

    else
    {
        ClientProgram(&args, &solves);
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

    return number_of_scanned_args; //количество возвращённых элементов равно коду ошибки
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

void InvalidInput(const int code_of_error, bool * ptr_need_to_continue)
{
    assert(ptr_need_to_continue != NULL);

    if (code_of_error == ERROR_A || code_of_error == ERROR_B || code_of_error == ERROR_C)
    {
        printf("Аргумент %c введён неверно. Введите данные заново "
               "(сначала коэффициент при x^2, потом при x, потом свободный): ", 97+code_of_error);
        SkipString();
    }

    else if (code_of_error == ERROR_EOF)
    {
        printf("Конец файла.");
        *ptr_need_to_continue = false;
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
        *ptr_need_to_continue = false;
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

void TestModeGreetings(void)
{
    printf("Начинаю unit-тестирование модуля SolutionsOfEquations.\n");
}

void RunTests(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves, const int number_of_random_tests, const bool visible_args)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    RunSpecialTests(ptr_args, ptr_solves, visible_args);

    RunRandomTests(ptr_args, ptr_solves, number_of_random_tests, visible_args);

    printf("Успешное тестирование. Пройдено %d/%d тестов.\n", number_of_random_tests+NUMBER_OF_SPECIAL_TESTS, number_of_random_tests+NUMBER_OF_SPECIAL_TESTS);
}

int StringToNumber(const char * str)
{
    assert(str != NULL);

    for (int number_of_element = 0; number_of_element < int (strlen(str)); number_of_element++)
    {
        if (not isdigit(str[number_of_element]))
        {
            InvalidCommand();
            return false;
        }
    }

    return atoi(str);
}

void InvalidCommand(void)
{
    printf("Ошибка в аргументах командной строки. Вот пример правильного ввода:\n"
           "name_of_file test number_of_random_tests (по умолчанию 1000, можно задать"
           " своё значение) -v (вывод проверяемых аргументов, без флага не выводятся)");
}

void RunSpecialTests(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves, const bool visible_args)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    for (int first_arg = 0; first_arg < 2; first_arg++)
    {
        for (int second_arg = 0; second_arg < 2; second_arg++)
        {
            for (int third_arg = 0; third_arg < 2; third_arg++)
            {
            ptr_args->a = first_arg;
            ptr_args->b = second_arg;
            ptr_args->c = third_arg;

            PrintArgs(ptr_args, visible_args);

            *ptr_solves = { };

            SolutionsOfEquations(ptr_args, ptr_solves);
            }
        }
    }
}

void RunRandomTests(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves, const int number_of_random_tests, const bool visible_args)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    for (int iteration = 0; iteration < number_of_random_tests; iteration++)
    {
        ptr_args->a = (RAND_MAX/2-rand())/ACCURACY;
        ptr_args->b = (RAND_MAX/2-rand())/ACCURACY;
        ptr_args->c = (RAND_MAX/2-rand())/ACCURACY;

        PrintArgs(ptr_args, visible_args);

        *ptr_solves = { };

        SolutionsOfEquations(ptr_args, ptr_solves);
    }
}

void PrintArgs(const struct EquationArgs * const ptr_args, const bool visible_args)
{
    assert(ptr_args != NULL);

    if (visible_args)
    {
        printf("a = %.3lf, b = %.3lf, c = %.3lf\n", ptr_args->a, ptr_args->b, ptr_args->c);
    }
}

void ClientProgram(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    Greetings();

    bool need_to_continue = true;

    while (need_to_continue)
    {
        int code_of_error = VerificationOfEnteredData(ptr_args);

        if (code_of_error == NO_ERRORS)
        {
            SolutionsOfEquations(ptr_args, ptr_solves);

            PrintEnding(ptr_args, ptr_solves);

            ContinueOrStop(&need_to_continue);
        }

        else
        {
            InvalidInput(code_of_error, &need_to_continue);
        }
    }
}

void TestingProgram(struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves, const int argc, const char * const argv[])
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);
    assert(argv != NULL);

    if (argc == MINIMUM_ARGS_FOR_TEST)
    {
        bool visible_args = false;
        int number_of_random_tests = 1000;
        TestModeGreetings();
        RunTests(ptr_args, ptr_solves, number_of_random_tests, visible_args);
    }

    else if (argc == MINIMUM_ARGS_FOR_TEST+1)
    {
        if (strcmp(argv[MINIMUM_ARGS_FOR_TEST], "-v") == 0)
        {
            bool visible_args = true;
            int number_of_random_tests = 1000;
            TestModeGreetings();
            RunTests(ptr_args, ptr_solves, number_of_random_tests, visible_args);
        }

        else
        {
            bool visible_args = false;

            if (int number_of_random_tests = StringToNumber(argv[MINIMUM_ARGS_FOR_TEST])) //если поданная строка содержит что-то кроме цифр, то возвращается false
            {
                TestModeGreetings();
                RunTests(ptr_args, ptr_solves, number_of_random_tests, visible_args);
            }
        }
    }

    else if (argc == MINIMUM_ARGS_FOR_TEST+2 && strcmp(argv[MINIMUM_ARGS_FOR_TEST+1], "-v") == 0)
    {
        bool visible_args = true;

        if (int number_of_random_tests = StringToNumber(argv[MINIMUM_ARGS_FOR_TEST])) //если поданная строка содержит что-то кроме цифр, то возвращается false
        {
            TestModeGreetings();
            RunTests(ptr_args, ptr_solves, number_of_random_tests, visible_args);
        }
    }

    else
    {
        InvalidCommand();
    }
}
