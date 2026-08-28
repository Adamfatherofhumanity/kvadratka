/// @defgroup kvadratka_solving
/// @ingroup kvadratka_solving
/// @{

/**
 * @brief solves quadratic equations with any arguments
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[out] ptr_solves pointer to a structure containing solutions
 * @return true if solution is correct
 * @return false if solution is incorrect
 */
bool SolutionsOfEquations(const EquationArgs * const ptr_args, EquationSolves * const ptr_solves);

/**
 * @brief solves quadratic equations (a != 0)
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[out] ptr_solves pointer to a structure containing solutions
 * @return true if solution is correct
 * @return false if solution is incorrect
 */
bool SolutionsOfQuadraticEquations(const EquationArgs * const ptr_args, EquationSolves * const ptr_solves);

/**
 * @brief solves linear equations with any arguments
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[out] ptr_solves pointer to a structure containing solutions
 * @return true if solution is correct
 * @return false if solution is incorrect
 */
bool SolutionsOfLinealEquations(const EquationArgs * const ptr_args, EquationSolves * const ptr_solves);



/**
 * @brief checks the correctness of the solution to a quadratic equation with two roots
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[in] ptr_solves pointer to a structure containing solutions
 * @return true if solution is correct
 * @return false if solution is incorrect
 */
bool CheckTwoRoots(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves);

/**
 * @brief checks the correctness of the solution to a quadratic equation with a single root
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[in] ptr_solves pointer to a structure containing solutions
 * @return true if solution is correct
 * @return false if solution is incorrect
 */
bool CheckOneRoot(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves);

/// @}
