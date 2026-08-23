#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

const double EPS = 1e-6;

const int MINIMUM_ARGS_FOR_TEST = 2;
const int DEFAULT_NUMBER_OF_RANDOM_TESTS = 1000;
const double ACCURACY = 1000;

const int ARGC_FOR_HELP = 2;

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

struct TestCase
{
    struct EquationArgs args;
    struct EquationSolves reference_solves;
};

const struct TestCase SPECIAL_TESTS_VALUES[] = {{{.a = 0, .b = 0, .c = 0}, {.number_of_solves = INF_SOLVES}},
    {{.a = 0, .b = 0, .c = 1}, {.number_of_solves = ZERO_SOLVES}},
    {{.a = 0, .b = 1, .c = 1}, {.number_of_solves = ONE_SOLVE, .solve1 = -1}},
    {{.a = 1, .b = 1, .c = 1}, {.number_of_solves = ZERO_SOLVES}},
    {{.a = 1, .b = 2, .c = 1}, {.number_of_solves = ONE_SOLVE, .solve1 = -1, .solve2 = -1}},
    {{.a = 1, .b = 5, .c = 6}, {.number_of_solves = TWO_SOLVES, .solve1 = -2, .solve2 = -3}}};

int ComparisonOfFractalNumbers(const double a, const double b);

bool SolutionsOfEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);
bool SolutionsOfQuadraticEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);
bool SolutionsOfLinealEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves);

int VerificationOfEnteredData(struct EquationArgs * const ptr_args);
void InvalidInput(const int code_of_error, bool * ptr_need_to_continue);
void InvalidAnswer(void);
bool CheckString(void);

void Greetings(void);
void PrintEnding(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
int ContinueOrStop(bool * ptr_need_to_continue);

bool CheckQuadraticRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
bool CheckLinealRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
bool CheckEquationErrors(void);

void SkipString(void);

void RunTests(const int number_of_random_tests, const bool visible_values);
int RunSpecialTests(const bool visible_values);
int RunRandomTests(const int number_of_random_tests, const bool visible_values);
int RunOneTest(const struct TestCase * const ptr_test, const bool visible_values);

void TestModeGreetings(void);
void InvalidCommand(void);
void PrintValues(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves, const bool visible_values);

void ClientProgram();
void TestingProgram(const int argc, const char * const argv[]);

void Help(void);
int SpecialTestsCounter(const struct TestCase * const ptr_test, const bool visible_values);

int main(int argc, char * argv[])
{
    if (argc == ARGC_FOR_HELP && strcmp(argv[ARGC_FOR_HELP-1], "--help") == 0)
    {
        Help();
    }

    else if (argc >= MINIMUM_ARGS_FOR_TEST && strcmp(argv[MINIMUM_ARGS_FOR_TEST-1], "test") == 0)
    {
        TestingProgram(argc, argv);
    }

    else
    {
        ClientProgram();
    }

    return 0;
}

bool SolutionsOfEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (ComparisonOfFractalNumbers(ptr_args->a, 0.0) == EQUAL)
    {
        return SolutionsOfLinealEquations(ptr_args, ptr_solves);
    }

    else
    {
        return SolutionsOfQuadraticEquations(ptr_args, ptr_solves);
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

bool SolutionsOfQuadraticEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double discriminant = ptr_args->b * ptr_args->b - 4 * ptr_args->a * ptr_args->c;

    if (discriminant < 0)
    {
        ptr_solves->number_of_solves = ZERO_SOLVES;
        return true;
    }

    else if (ComparisonOfFractalNumbers(discriminant, 0.0) == EQUAL)
    {
        ptr_solves->solve1 = (-ptr_args->b) / (2 * ptr_args->a);
        ptr_solves->solve2 = (-ptr_args->b) / (2 * ptr_args->a);
        ptr_solves->number_of_solves = ONE_SOLVE;

        return CheckQuadraticRoots(ptr_args, ptr_solves);
    }

    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        ptr_solves->solve1 = (-ptr_args->b - sqrt_discriminant) / (2 * ptr_args->a);
        ptr_solves->solve2 = (-ptr_args->b + sqrt_discriminant) / (2 * ptr_args->a);
        ptr_solves->number_of_solves = TWO_SOLVES;

        return CheckQuadraticRoots(ptr_args, ptr_solves);
    }
}

bool SolutionsOfLinealEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (ComparisonOfFractalNumbers(ptr_args->b, 0.0) == EQUAL)
    {
        if (ComparisonOfFractalNumbers(ptr_args->c, 0.0) == EQUAL)
        {
            ptr_solves->number_of_solves = INF_SOLVES;
            return true;
        }

        else
        {
            ptr_solves->number_of_solves = ZERO_SOLVES;
            return true;
        }
    }

    else
    {
        ptr_solves->solve1 = (-ptr_args->c) / ptr_args->b;
        ptr_solves->number_of_solves = ONE_SOLVE;

        return CheckLinealRoots(ptr_args, ptr_solves);
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
        if (! CheckString())
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

bool CheckQuadraticRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double value1 = ptr_args->a * ptr_solves->solve1 * ptr_solves->solve1 + ptr_args->b * ptr_solves->solve1 + ptr_args->c;
    double value2 = ptr_args->a * ptr_solves->solve2 * ptr_solves->solve2 + ptr_args->b * ptr_solves->solve2 + ptr_args->c;

    if (ComparisonOfFractalNumbers(value1, 0.0) != EQUAL || ComparisonOfFractalNumbers(value2, 0.0) != EQUAL)
    {
        printf("Произошла ошибка в вычислениях.\n");
        printf("a = %lf, b = %lf, c = %lf, x1 = %lf, x2 = %lf.\n", ptr_args->a, ptr_args->b, ptr_args->c, ptr_solves->solve1, ptr_solves->solve2);

        return false;
    }

    return true;
}

bool CheckLinealRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double value = ptr_args->b * ptr_solves->solve1 + ptr_args->c;

    if (ComparisonOfFractalNumbers(value, 0.0) != EQUAL)
    {
        printf("Произошла ошибка в вычислениях.\n");
        printf("b = %lf, c = %lf, x = %lf.\n", ptr_args->b, ptr_args->c, ptr_solves->solve1);

        return false;
    }

    return true;
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

void RunTests(const int number_of_random_tests, const bool visible_values)
{
    if (visible_values)
    {
        printf("\nНачинаю прохождение заданных тестов.\n\n");
    }

    int success_special_tests = RunSpecialTests(visible_values);

    if (visible_values)
    {
        printf("\nНачинаю прохождение рандомных тестов.\n\n");
    }

    int success_random_tests = RunRandomTests(number_of_random_tests, visible_values);

    printf("\nУспешное тестирование. Пройдено %d/%d заданных тестов и %d/%d рандомных тестов.\n", success_special_tests, sizeof (SPECIAL_TESTS_VALUES) / sizeof (TestCase), success_random_tests, number_of_random_tests);
}

void InvalidCommand(void)
{
    printf("Ошибка в аргументах командной строки. Для получения помощи в использовании программы введите \n"
           "name_of_file --help в командную строку\n");
}

int RunSpecialTests(const bool visible_values)
{
    int success_special_tests = 0;

    for (size_t iteration = 0; iteration < sizeof (SPECIAL_TESTS_VALUES) / sizeof (TestCase); iteration++)
    {
        success_special_tests = SpecialTestsCounter(&SPECIAL_TESTS_VALUES[iteration], visible_values);
    }

    return success_special_tests;
}

int RunRandomTests(const int number_of_random_tests, const bool visible_values)
{
    struct EquationArgs args = { };
    struct EquationSolves solves = { };

    int success_random_tests = 0;

    for (int iteration = 0; iteration < number_of_random_tests; iteration++)
    {
        args = {.a = (RAND_MAX/2-rand())/ACCURACY, .b = (RAND_MAX/2-rand())/ACCURACY, .c = (RAND_MAX/2-rand())/ACCURACY};

        solves = { };

        if (SolutionsOfEquations(&args, &solves))
        {
            success_random_tests += 1;
        }

        PrintValues(&args, &solves, visible_values);
    }

    return success_random_tests;
}

void PrintValues(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves, const bool visible_values)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (visible_values)
    {
        printf("a = %7.3lf, b = %7.3lf, c = %7.3lf, number_of_solves = %d, x1 = %7.3lf, x2 = %7.3lf\n",
         ptr_args->a, ptr_args->b, ptr_args->c, ptr_solves->number_of_solves, ptr_solves->solve1, ptr_solves->solve2);
    }
}

void ClientProgram()
{
    struct EquationArgs args = { };
    struct EquationSolves solves = { };

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
            InvalidInput(code_of_error, &need_to_continue);
        }
    }
}

void TestingProgram(const int argc, const char * const argv[])
{
    assert(argv != NULL);

    bool visible_values = false;
    int number_of_random_tests = DEFAULT_NUMBER_OF_RANDOM_TESTS;

    for (int number_of_arg = MINIMUM_ARGS_FOR_TEST; number_of_arg < argc; number_of_arg++)
    {
        if (strcmp(argv[number_of_arg], "-v") == 0)
        {
            visible_values = true;
            break;
        }
    }

    for (int number_of_arg = MINIMUM_ARGS_FOR_TEST; number_of_arg < argc; number_of_arg++)
    {
        if (atoi(argv[number_of_arg]))
        {
            number_of_random_tests = atoi(argv[number_of_arg]);
            break;
        }
    }

    TestModeGreetings();
    RunTests(number_of_random_tests, visible_values);
}

int RunOneTest(const struct TestCase * const ptr_test, const bool visible_values)
{
    assert(ptr_test != NULL);

    struct EquationSolves solves = { };

    SolutionsOfEquations(&(ptr_test->args), &solves);

    double solve1 = solves.solve1;
    double solve2 = solves.solve2;

    double reference_solve1 = (ptr_test->reference_solves).solve1;
    double reference_solve2 = (ptr_test->reference_solves).solve2;

    if (! (solves.number_of_solves == (ptr_test->reference_solves).number_of_solves &&
    ((ComparisonOfFractalNumbers(solve1, reference_solve1) == EQUAL && ComparisonOfFractalNumbers(solve2, reference_solve2) == EQUAL) ||
    (ComparisonOfFractalNumbers(solve1, reference_solve2) == EQUAL && ComparisonOfFractalNumbers(solve2, reference_solve1) == EQUAL))))
    {
        printf("Произошла ошибка в вычислениях.\n");

        printf("a = %.3lf, b = %.3lf, c = %.3lf, number_of_solves = %d, x1 = %.3lf, x2 = %.3lf.\n",
        (ptr_test->args).a, (ptr_test->args).b, (ptr_test->args).c, solves.number_of_solves, solve1, solve2);

        printf("number_of_solves_ref = %d, x1_ref = %.3lf, x2_ref = %.3lf\n", (ptr_test->reference_solves).number_of_solves, reference_solve1, reference_solve2);

        return 0;
    }

    else
    {
        PrintValues(&(ptr_test->args), &solves, visible_values);
        return 1;
    }
}

void Help(void)
{
    printf("У программы есть 2 режима: тестирование и взаимодействие с пользователем.\n");
    printf("Для режима тестирования надо ввести определённые аргументы в командную строку. Вот пример правильного ввода:\n"
           "name_of_file test number_of_random_tests (по умолчанию 1000, можно задать"
           " своё значение) -v (вывод проверяемых аргументов, без флага не выводятся)\n");
    printf("В остальных случаях запустится режим взаимодействия с пользователем.\n");
}

int SpecialTestsCounter(const struct TestCase * const ptr_test, const bool visible_values)
{
    static int special_tests_counter = 0;

    special_tests_counter += RunOneTest(ptr_test, visible_values);
    return special_tests_counter;
}

// TODO: fopen fclose fseek прочитать
