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
const int NUMBER_OF_ARGS = 3;

const int ARGC_FOR_HELP = 2;

const char DEFAULT_NAME_OF_FILE[] = "test.txt";

const int CODE_OF_CTRL_Z = 26;

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
    double solve1;
    double solve2;
    int number_of_solves;
};

struct TestCase
{
    struct EquationArgs args;
    struct EquationSolves reference_solves;
};

const struct TestCase SPECIAL_TESTS_VALUES[] = {{{.a = 0, .b = 0, .c = 0}, {.solve1 = NAN, .solve2 = NAN, .number_of_solves = INF_SOLVES}},
                                                {{.a = 0, .b = 0, .c = 1}, {.solve1 = NAN, .solve2 = NAN, .number_of_solves = ZERO_SOLVES}},
                                                {{.a = 0, .b = 1, .c = 1}, {.solve1 = -1, .solve2 = NAN, .number_of_solves = ONE_SOLVE}},
                                                {{.a = 1, .b = 1, .c = 1}, {.solve1 = NAN, .solve2 = NAN, .number_of_solves = ZERO_SOLVES}},
                                                {{.a = 1, .b = 2, .c = 1}, {.solve1 = -1, .solve2 = NAN, .number_of_solves = ONE_SOLVE}},
                                                {{.a = 1, .b = 5, .c = 6}, {.solve1 = -2, .solve2 = -3, .number_of_solves = TWO_SOLVES}}};

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

bool CheckTwoRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
bool CheckOneRoot(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
bool CheckEquationErrors(void);

void SkipString(void);

void RunTests(const int number_of_random_tests, const bool visible_values);
int RunSpecialTests(const bool visible_values);
int RunRandomTests(const int number_of_random_tests, const bool visible_values);
bool RunOneTest(const struct TestCase * const ptr_test, const bool visible_values);

void TestModeGreetings(void);
void InvalidCommand(void);
void PrintValues(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves, const bool visible_values);

void ClientProgram();
void TestingProgram(const int argc, char * argv[]);

void Help(void);

void RunFileTests(const char * const ptr_name_of_file, const bool visible_values);

bool CheckOneSolve(const struct TestCase * const ptr_test, const bool visible_values);
bool CheckTwoSolves(const struct TestCase * const ptr_test, const bool visible_values);
bool CheckInfOrZeroSolves(const struct TestCase * const ptr_test, const bool visible_values);

bool PrintSolve(const struct TestCase * const ptr_test, const struct EquationSolves * const ptr_solves, const bool visible_values, const bool right_solve);
void SortDoubles(double * ptr_a, double * ptr_b);
void PrintErrorValues(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves);
void ErrorInCalc(void);

#include "input_and_output.cpp"
#include "solving.cpp"
#include "testing.cpp"
#include "support_functions.cpp"

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

void ClientProgram()
{
    struct EquationArgs args = { };
    struct EquationSolves solves = {.solve1 = NAN, .solve2 = NAN};

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

void TestingProgram(const int argc, char * argv[])
{
    assert(argv != NULL);

    bool visible_values = false;
    int number_of_random_tests = DEFAULT_NUMBER_OF_RANDOM_TESTS;
    bool file_testing = false;
    const char * ptr_name_of_file = DEFAULT_NAME_OF_FILE;

    for (int number_of_arg = MINIMUM_ARGS_FOR_TEST; number_of_arg < argc; number_of_arg++)
    {
        if (strcmp(argv[number_of_arg], "-f") == 0)
        {
            file_testing = true;
        }

        else if (strcmp(argv[number_of_arg], "-v") == 0)
        {
            visible_values = true;
        }

        else if (atoi(argv[number_of_arg]))
        {
            number_of_random_tests = atoi(argv[number_of_arg]);
        }

        else
        {
            ptr_name_of_file = argv[number_of_arg];
        }
    }

    TestModeGreetings();
    if (file_testing)
    {
        RunFileTests(ptr_name_of_file, visible_values);
    }

    else
    {
        RunTests(number_of_random_tests, visible_values);
    }
}
