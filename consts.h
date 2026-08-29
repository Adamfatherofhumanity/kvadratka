/// @defgroup kvadratka_consts
/// @ingroup kvadratka_consts
/// @{

const double EPS = 1e-6; ///< tolerance for comparing doubles
const int NUMBER_OF_EQUATION_ARGS = 3; ///< number of arguments of a quadratic equation
const int CODE_OF_CTRL_Z = 26; ///< ctrl+z code (simulating end-of-file)
const double ACCURACY = 1000; ///< precision of generated random doubles
const int MAX_LEN_OF_FILENAME = 81; ///< default test filename

enum CodeOfModes
{
    CLIENT_MODE = 1, ///< code of client mode
    TEST_MODE = 2, ///< code of test mode
    QUIT = 0 ///< code of quit mode
};

enum CodeOfClientModeAnswers
{
    CONTINUE = 1, ///< code of continuation of solving equations
    BACK = 0 ///< code of back to start menu
};

enum CodeOfYesOrNoAnswers
{
    YES = 1, ///< code of "yes" answer
    NO = 0 ///< code of "no" answer
};

enum Comparison
{
    BIGGER = 1, ///< a constant indicating that the first number is greater than the second
    SMALLER = -1, ///< a constant indicating that the first number is less than the second
    EQUAL = 0 ///< a constant indicating that the first number is equal to the second
};

enum Solves
{
    INF_SOLVES = 3, ///< a constant indicating that the equation has infinitely many solutions
    ZERO_SOLVES = 0, ///< a constant indicating that the equation has zero solutions
    ONE_SOLVE = 1, ///< a constant indicating that the equation has one solution
    TWO_SOLVES = 2 ///< a constant indicating that the equation has two solutions
};

enum CodeOfEquationErrors
{
    ERROR_EOF = -1, ///< end-of-file error code
    ERROR_A = 0, ///< error code in argument a
    ERROR_B = 1, ///< error code in argument b
    ERROR_C = 2, ///< error code in argument c
    NO_ERRORS = 3, ///< error-free code
    ERROR_SO_MANY = 4, ///< error code for too many arguments
};

/// @}

/// @defgroup kvadratka_types
/// @ingroup kvadratka_types
/// @{

/**
 * @brief a structure consisting of the arguments of a quadratic equation
 */
struct EquationArgs
{
    double a; ///< coefficient of x**2
    double b; ///< coefficient of x
    double c; ///< free coefficient
};

/**
 * @brief a structure consisting of the solutions to a quadratic equation
 */
struct EquationSolves
{
    double solve1; ///< first solve
    double solve2; ///< second solve
    int number_of_solves; ///< number of solves
};

/**
 * @brief a structure consisting of the argument structure and the structure of reference solutions for a quadratic equation
 */
struct TestCase
{
    EquationArgs args; ///< a structure consisting of the arguments of a quadratic equation
    EquationSolves reference_solves; ///< a structure consisting of the reference solutions to a quadratic equation
};

/// @}

/// @ingroup kvadratka_consts
/// @{

/**
 * @brief an array of test structures, each consisting of an argument structure and a reference solution structure for a quadratic equation
 */
const TestCase SPECIAL_TESTS_VALUES[] = {{{.a = 0, .b = 0, .c = 0}, {.solve1 = NAN, .solve2 = NAN, .number_of_solves = INF_SOLVES}},
                                         {{.a = 0, .b = 0, .c = 1}, {.solve1 = NAN, .solve2 = NAN, .number_of_solves = ZERO_SOLVES}},
                                         {{.a = 0, .b = 1, .c = 1}, {.solve1 = -1, .solve2 = NAN, .number_of_solves = ONE_SOLVE}},
                                         {{.a = 1, .b = 1, .c = 1}, {.solve1 = NAN, .solve2 = NAN, .number_of_solves = ZERO_SOLVES}},
                                         {{.a = 1, .b = 2, .c = 1}, {.solve1 = -1, .solve2 = NAN, .number_of_solves = ONE_SOLVE}},
                                         {{.a = 1, .b = 5, .c = 6}, {.solve1 = -2, .solve2 = -3, .number_of_solves = TWO_SOLVES}}};

/// @}
