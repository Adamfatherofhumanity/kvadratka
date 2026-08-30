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
void TestMode(void);



/**
 * @brief prompts the user to enter arguments
 */
void RequestForArguments(void);

/**
 * @brief prompts the user to enter answer
 */
void RequestForAnswer(void);

/**
 * @brief prompts the user to enter filename
 */
void RequestForFilename(void);

/**
 * @brief prompts the user to enter number of random tests
 */
void RequestForNumberOfRandomTests(void);

/**
 * @brief prompts the user to click escape
 */
void RequestForEscape(void);



/**
 * @brief displaying the start menu for using program (to choose mode)
 */
void StartMenu(void);

/**
 * @brief validates the input answer and returns code of choosen mode
 *
 * @return int code of mode (CLIENT_MODE/TEST_MODE/QUIT)
 */
int StartMenuAnswer(void);

/**
 * @brief displays a message about an invalid response format in start menu [s(S)/t(T)/q(Q)]
 */
void InvalidStartMenuAnswer(void);



/**
 * @brief validates the input arguments and writes them to the structure
 *
 * @param[out] ptr_args pointer to the structure where the arguments are to be written
 * @return int code of error (ERROR_EOF/ERROR_A/ERROR_B/ERROR_C/NO_ERRORS/ERROR_SO_MANY/)
 */
int VerificationOfEnteredData(EquationArgs * const ptr_args);

/**
 * @brief displays an error message based on its code and switches the flag in case of a critical error
 *
 * @param[in] code_of_error code of error
 * @param[out] ptr_need_to_continue pointer to a flag that toggles if a critical error occurs
 */
void InvalidInput(const int code_of_error, bool * ptr_need_to_continue);

/**
 * @brief outputs the quadratic equation and its solutions
 *
 * @param[in] ptr_args pointer to a structure containing arguments
 * @param[in] ptr_solves pointer to a structure containing solutions
 */
void PrintEnding(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves);



/**
 * @brief asks the user if they want to continue solving equations
 */
void ClientModeMenu(void);

/**
 * @brief validates the input answer and returns code of chosen answer
 *
 * @return int code of chosen answer (CONTINUE/BACK)
 */
int ClientModeMenuAnswer(void);

/**
 * @brief displays a message about an invalid response format in client mode menu [c(C)/b(B)]
 */
void InvalidClientModeMenuAnswer(void);



/**
 * @brief asks the user if they want to see arguments and solves of success tests
 */
void VisibleValuesMenu(void);

/**
 * @brief validates the input answer and returns code of chosen answer
 *
 * @return int code of chosen answer (YES/NO)
 */
int VisibleValuesMenuAnswer(void);



/**
 * @brief offers "yes" or "no" answer options
 */
void YesOrNoMenu(void);

/**
 * @brief displays a message about an invalid response format in "yes" or "no" menu [y(Y)/n(N)]
 */
void InvalidYesOrNoMenuAnswer(void);



/**
 * @brief asks the user if they want to runs tests from file
 */
void FileTestsMenu(void);

/**
 * @brief validates the input answer and returns code of chosen answer
 *
 * @return int code of chosen answer (YES/NO)
 */
int FileTestsMenuAnswer(void);



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
 * @brief displays a calculation error message
 */
void ErrorInCalc(void);

/// @}
