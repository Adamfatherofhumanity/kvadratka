#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "consts.h"
#include "input_and_output.h"
#include "solving.h"
#include "testing.h"
#include "support_functions.h"

#include "input_and_output.cpp"
#include "solving.cpp"
#include "testing.cpp"
#include "support_functions.cpp"

/// @ingroup kvadratka
/**
 * @brief interacts with the user
 */
void ClientProgram();

/// @ingroup kvadratka
/**
 * @brief test mode
 *
 * @param[in] argc number of command-line arguments
 * @param[in] argv pointer to an array of command-line arguments
 */
void TestingProgram(const int argc, char * argv[]);

/**
 * @brief the main function with which the program begins
 *
 * @param argc number of command-line arguments
 * @param argv pointer to an array of command-line arguments
 * @return int 0
 */
int main(int argc, char * argv[])
{
    if (argv != NULL)
    {
        if (argc == ARGC_FOR_HELP && strcmp(argv[ARGC_FOR_HELP-1], "--help") == 0)
        {
            Help();
        }

        else if (argc >= MINIMUM_ARGC_FOR_TEST && argc <= MAXIMUM_ARGC_FOR_TEST && strcmp(argv[MINIMUM_ARGC_FOR_TEST-1], "test") == 0)
        {
            TestingProgram(argc, argv);
        }

        else if (argc == ARGC_FOR_CLIENT_MODE)
        {
            ClientProgram();
        }

        else
        {
            InvalidCommand();
        }
    }

    else
    {
        printf("Ошибка в считывании аргументов командной строки.\n");
    }

    return 0;
}

void ClientProgram()
{
    EquationArgs args = { };
    EquationSolves solves = {.solve1 = NAN, .solve2 = NAN};

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

    for (size_t number_of_arg = MINIMUM_ARGC_FOR_TEST; number_of_arg < size_t (argc); number_of_arg++)
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
