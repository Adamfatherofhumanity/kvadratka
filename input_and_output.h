/// @defgroup kvadratka_input_and_output
/// @ingroup kvadratka_input_and_output
/// @{

/**
 * @brief greeting in user interaction mode
 */
void Greetings(void);

/**
 * @brief greeting in test mode
 */
void TestModeGreetings(void);

/**
 * @brief displaying the program usage guide
 */
void Help(void);



/**
 * @brief validates the input arguments and writes them to the structure
 *
 * @param[out] ptr_args pointer to the structure where the arguments are to be written
 * @return int code of error
 */
int VerificationOfEnteredData(EquationArgs * const ptr_args);

/**
 * @brief outputs the quadratic equation and its solutions
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[in] ptr_solves pointer to a structure containing solutions
 */
void PrintEnding(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves);

/**
 * @brief asks the user if they want to continue.
 *
 * @param[out] ptr_need_to_continue pointer to a flag that is toggled if the user declines to continue.
 * @return int 0 to break the infinite loop
 */
int ContinueOrStop(bool * ptr_need_to_continue);

/**
 * @brief displays an error message based on its code and switches the flag in case of a critical error
 *
 * @param[in] code_of_error code of error
 * @param[out] ptr_need_to_continue pointer to a flag that toggles if a critical error occurs
 */
void InvalidInput(const int code_of_error, bool * ptr_need_to_continue);



/**
 * @brief derivation of a quadratic equation from arguments
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 */
void PrintEq(const EquationArgs * const ptr_args);

/**
 * @brief outputs the arguments and solutions of the equation
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[in] ptr_solves pointer to a structure containing solutions
 * @param[in] visible_values flag indicating whether to output data
 */
void PrintValues(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves, const bool visible_values);

/**
 * @brief outputs equation arguments and solutions along with reference solutions if the solution is incorrect,
 * or only arguments and solutions if the solution is correct
 *
 * @param[in] ptr_test pointer to a structure consisting of an arguments structure and a reference solutions structure
 * @param[in] ptr_solves pointer to a structure containing solutions
 * @param[in] visible_values flag indicating whether to output data if the solution is correct
 * @param[in] false_solve flag indicating whether the solution is incorrect
 * @return true if the solution is correct
 * @return false if the solution is incorrect
 */
bool PrintSolve(const TestCase * const ptr_test, const EquationSolves * const ptr_solves, const bool visible_values, const bool false_solve);

/**
 * @brief outputs the arguments and solutions of the equation (called in the event of a calculation error)
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[in] ptr_solves pointer to a structure containing solutions
 */
void PrintErrorValues(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves);



/**
 * @brief displays a message about an invalid response format [Y/N]
 */
void InvalidAnswer(void);

/**
 * @brief outputs an error message regarding command-line arguments
 */
void InvalidCommand(void);

/**
 * @brief displays a calculation error message
 */
void ErrorInCalc(void);

/// @}
