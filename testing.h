/// @defgroup kvadratka_testing
/// @ingroup kvadratka_testing
/// @{

/**
 * @brief runs specified and random tests
 *
 * @param[in] number_of_random_tests number of random tests
 * @param[in] visible_values a flag indicating whether to output the arguments and the resulting solutions of the quadratic equation
 */
void RunTests(const int number_of_random_tests, const bool visible_values);

/**
 * @brief runs tests from a file
 *
 * @param[in] ptr_name_of_file pointer to a filename
 * @param[in] visible_values a flag indicating whether to output the arguments and the resulting solutions of the quadratic equation
 */
void RunFileTests(const char * const ptr_name_of_file, const bool visible_values);

/**
 * @brief runs the specified tests
 *
 * @param[in] visible_values a flag indicating whether to output the arguments and the resulting solutions of the quadratic equation
 * @return int number of successfully passed specified tests
 */
int RunSpecialTests(const bool visible_values);

/**
 * @brief runs the random tests
 *
 * @param[in] number_of_random_tests number of random tests
 * @param[in] visible_values a flag indicating whether to output the arguments and the resulting solutions of the quadratic equation
 * @return int number of successfully passed random tests
 */
int RunRandomTests(const int number_of_random_tests, const bool visible_values);

/**
 * @brief runs one test
 *
 * @param[in] ptr_test a pointer to a structure consisting of an argument structure and a structure for the reference solution to the quadratic equation
 * @param[in] visible_values a flag indicating whether to output the arguments and the resulting solutions of the quadratic equation
 * @return true if the test is passed
 * @return false if the test is not passed
 */
bool RunOneTest(const TestCase * const ptr_test, const bool visible_values);



/**
 * @brief initiates the solution of a quadratic equation and compares the resulting solutions with reference solutions,
 * handling cases where the reference solutions are zero or infinite
 *
 * @param[in] ptr_test a pointer to a structure consisting of an argument structure and a structure for the reference solution to the quadratic equation
 * @param[in] visible_values a flag indicating whether to output the arguments and the resulting solutions of the quadratic equation
 * @return true if the solutions matched the reference ones
 * @return false if the solutions did not match the reference ones
 */
bool CheckInfOrZeroSolves(const TestCase * const ptr_test, const bool visible_values);

/**
 * @brief initiates the solution of a quadratic equation and compares the resulting solutions with reference solutions,
 * handling cases where the reference solutions are two
 *
 * @param[in] ptr_test a pointer to a structure consisting of an argument structure and a structure for the reference solution to the quadratic equation
 * @param[in] visible_values a flag indicating whether to output the arguments and the resulting solutions of the quadratic equation
 * @return true if the solutions matched the reference ones
 * @return false if the solutions did not match the reference ones
 */
bool CheckTwoSolves(const TestCase * const ptr_test, const bool visible_values);

/**
 * @brief initiates the solution of a quadratic equation and compares the resulting solutions with reference solutions,
 * handling cases where the reference solutions are one
 *
 * @param[in] ptr_test a pointer to a structure consisting of an argument structure and a structure for the reference solution to the quadratic equation
 * @param[in] visible_values a flag indicating whether to output the arguments and the resulting solutions of the quadratic equation
 * @return true if the solutions matched the reference ones
 * @return false if the solutions did not match the reference ones
 */
bool CheckOneSolve(const TestCase * const ptr_test, const bool visible_values);

/// @}
