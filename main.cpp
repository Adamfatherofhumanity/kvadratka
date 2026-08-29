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

/// @defgroup kvadratka_modes
/// @ingroup kvadratka_modes
/// @{
/**
 * @brief interacts with the user
 */
void ClientProgram();

/**
 * @brief test mode
 */
void TestingProgram(void);

/// @}

/// @defgroup kvadratka_general
/// @ingroup kvadratka_general
/// @{
/**
 * @brief the main function with which the program begins
 *
 * @return int 0
 */
int main(void)
{
    Greetings();

    bool need_to_quit = false;

    while (!need_to_quit)
    {
        StartMenu();

        int code_of_mode = StartMenuAnswer();

        if (code_of_mode == CLIENT_MODE)
        {
            ClientProgram();
        }

        else if (code_of_mode == TEST_MODE)
        {
            TestingProgram();
        }

        else if (code_of_mode == QUIT)
        {
            need_to_quit = true;
        }
    }

    return 0;
}

/// @}

void ClientProgram()
{
    EquationArgs args = { };
    EquationSolves solves = {.solve1 = NAN, .solve2 = NAN};

    bool need_to_continue = true;
    RequestForArguments();

    while (need_to_continue)
    {
        int code_of_error = VerificationOfEnteredData(&args);

        if (code_of_error == NO_ERRORS)
        {
            SolutionsOfEquations(&args, &solves);
            PrintEnding(&args, &solves);

            ClientModeMenu();
            if (ClientModeMenuAnswer() == BACK)
            {
                need_to_continue = false;
            }

            else
            {
                RequestForArguments();
            }
        }

        else
        {
            InvalidInput(code_of_error, &need_to_continue);
        }
    }
}

void TestingProgram(void)
{
    bool visible_values = false;
    bool file_testing = false;
    char name_of_file[MAX_LEN_OF_FILENAME] = "";
    int number_of_random_tests = 0;

    VisibleValuesMenu();
    if (VisibleValuesMenuAnswer() == YES)
    {
        visible_values = true;
    }

    FileTestsMenu();
    if (FileTestsMenuAnswer() == YES)
    {
        file_testing = true;
        RequestForFilename();
        scanf("%80s", name_of_file); // 80 = MAX_LEN_OF_FILENAME-1
    }

    else
    {
        RequestForNumberOfRandomTests();
        scanf("%d", &number_of_random_tests);
    }

    if (file_testing)
    {
        RunFileTests(name_of_file, visible_values);
    }

    else
    {
        RunTests(number_of_random_tests, visible_values);
    }
}
