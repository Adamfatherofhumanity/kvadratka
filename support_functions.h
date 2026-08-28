/// @defgroup kvadratka_support_functions
/// @ingroup kvadratka_support_functions
/// @{

/**
 * @brief compares two fractional numbers
 *
 * @param[in] a the first number
 * @param[in] b the second number
 * @return int result of the comparison (BIGGER/SMALLER/EQUAL)
 */
int ComparisonOfFractalNumbers(const double a, const double b);

/**
 * @brief sorts two doubles in descending order
 *
 * @param[out] ptr_a pointer to first number
 * @param[out] ptr_b pointer to second number
 */
void SortDoubles(double * ptr_a, double * ptr_b);

/**
 * @brief generates a random double
 *
 * @return double generation result
 */
double RandDouble(void);

/**
 * @brief calculates the value of a quadratic equation
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[in] solve substituted value
 * @return double value of a quadratic equation
 */
double CalcValueOfQuadraticEq(const EquationArgs * const ptr_args, const double solve);

/**
 * @brief solves the problem of -0 and 0 solutions
 *
 * @param[out] ptr_solves pointer to a structure containing solutions
 */
void ZeroProblemSolve(EquationSolves * const ptr_solves);



/**
 * @brief checks the line of standard input for the presence of non-whitespace characters
 *
 * @return true if only whitespace characters
 * @return false if there are non-whitespace characters
 */
bool CheckString(void);

/**
 * @brief skips a line of standard input
 */
void SkipString(void);

/// @}
