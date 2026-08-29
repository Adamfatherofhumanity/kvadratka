void Greetings(void)
{
    printf("Приветствую, пользователь.\nЯ программа, умеющая решать квадратные уравнения.\n");
}

void TestMode(void)
{
    printf("\nНачинаю unit-тестирование модуля SolutionsOfEquations.\n\n");
}

void RequestForArguments(void)
{
    printf("\nВведите коэффициенты квадратного уравнения(сначала коэффициент при x^2, потом при x, потом свободный): ");
}

void RequestForAnswer(void)
{
    printf("\nВведите выбранный вариант: ");
}

void RequestForFilename(void)
{
    printf("\nВведите название файла, из которого необходимо брать тесты: ");
}

void RequestForNumberOfRandomTests(void)
{
    printf("\nВведите количество рандомных тестов, которое требуется провести: ");
}

void StartMenu(void)
{
    printf("\nВыберите режим работы программы (введите букву, соответствующую выбранному варианту):\n"
           "s) Решение уравнений, вводимых с клавиатуры\n"
           "t) Тестирование программы (запуск тестов из файла или генерация рандомных)\n\n"
           "q) Завершить работу программы\n");
    RequestForAnswer();
}

int StartMenuAnswer(void)
{
    int answer = 0;

    while (1)
    {
        while (isspace(answer = getchar()))
        {
            continue;
        }

        if (answer == 's' || answer == 'S')
        {
            if (CheckString())
            {
                return CLIENT_MODE;
            }
        }

        else if (answer == 't' || answer == 'T')
        {
            if (CheckString())
            {
                return TEST_MODE;
            }
        }

        else if (answer == 'q' || answer == 'Q')
        {
            if (CheckString())
            {
                return QUIT;
            }
        }

        else
        {
            SkipString();
        }

        InvalidStartMenuAnswer();
    }
}

void InvalidStartMenuAnswer(void)
{
    printf("Принимаются только ответы s(S)/t(T)/q(Q): ");
}

int VerificationOfEnteredData(EquationArgs * const ptr_args)
{
    assert(ptr_args != NULL);

    int number_of_scanned_args = scanf("%lf %lf %lf", &(ptr_args->a), &(ptr_args->b), &(ptr_args->c));

    if (number_of_scanned_args == NUMBER_OF_EQUATION_ARGS)
    {
        if (!CheckString())
        {
            number_of_scanned_args++;
        }
    }

    return number_of_scanned_args; //number_of_scanned_args <=> code_of_error
}

void InvalidInput(const int code_of_error, bool * ptr_need_to_continue)
{
    assert(ptr_need_to_continue != NULL);

    if (code_of_error == ERROR_A || code_of_error == ERROR_B || code_of_error == ERROR_C)
    {
        printf("Аргумент %c введён неверно. Введите данные заново "
               "(сначала коэффициент при x^2, потом при x, потом свободный): ", 'a' + code_of_error);
        SkipString();
    }

    else if (code_of_error == ERROR_EOF)
    {
        printf("Конец ввода.");
        *ptr_need_to_continue = false;
    }

    else if (code_of_error == ERROR_SO_MANY)
    {
        printf("Введены лишние аргументы. Введите данные заново "
               "(сначала коэффициент при x^2, потом при x, потом свободный): ");
    }

    else
    {
        printf("Произошла непредвиденная ошибка.\n");
        *ptr_need_to_continue = false;
    }
}

void PrintEnding(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    PrintEq(ptr_args);

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
            printf("ошибка в решении.\n");
            break;
    }
}

void ClientModeMenu(void)
{
    printf("\nЧто хотите делать дальше:\n"
           "c) Продолжить решение уравнений\n"
           "b) Вернуться в стартовое меню\n");
    RequestForAnswer();
}

int ClientModeMenuAnswer(void)
{
    int answer = 0;

    while (1)
    {
        while (isspace(answer = getchar()))
        {
            continue;
        }

        if (answer == 'c' || answer == 'C')
        {
            if (CheckString())
            {
                return CONTINUE;
            }
        }

        else if (answer == 'b' || answer == 'B')
        {
            if (CheckString())
            {
                return BACK;
            }
        }

        else
        {
            SkipString();
        }

        InvalidClientModeMenuAnswer();
    }
}

void InvalidClientModeMenuAnswer(void)
{
    printf("Принимаются только ответы c(C)/b(B): ");
}

void VisibleValuesMenu(void)
{
    printf("\nХотите видеть аргументы и полученные решения в верных тестах:\n");
    YesOrNoMenu();
    RequestForAnswer();
}

int VisibleValuesMenuAnswer(void)
{
    int answer = 0;

    while (1)
    {
        while (isspace(answer = getchar()))
        {
            continue;
        }

        if (answer == 'y' || answer == 'Y')
        {
            if (CheckString())
            {
                return YES;
            }
        }

        else if (answer == 'n' || answer == 'N')
        {
            if (CheckString())
            {
                return NO;
            }
        }

        else
        {
            SkipString();
        }

        InvalidYesOrNoMenuAnswer();
    }
}

void YesOrNoMenu(void)
{
    printf("y) Да\n"
           "n) Нет\n");
}

void InvalidYesOrNoMenuAnswer(void)
{
    printf("Принимаются только ответы y(Y)/n(N): ");
}

void FileTestsMenu(void)
{
    printf("\nХотите подключить тесты из файла:\n");
    YesOrNoMenu();
    RequestForAnswer();
}

int FileTestsMenuAnswer(void)
{
    int answer = 0;

    while (1)
    {
        while (isspace(answer = getchar()))
        {
            continue;
        }

        if (answer == 'y' || answer == 'Y')
        {
            if (CheckString())
            {
                return YES;
            }
        }

        else if (answer == 'n' || answer == 'N')
        {
            if (CheckString())
            {
                return NO;
            }
        }

        else
        {
            SkipString();
        }

        InvalidYesOrNoMenuAnswer();
    }
}

void PrintEq(const EquationArgs * const ptr_args)
{
    assert(ptr_args != NULL);

    double a = ptr_args->a;
    double b = ptr_args->b;
    double c = ptr_args->c;

    printf("\nУ уравнения ");

    if (ComparisonOfFractalNumbers(a, 0.0) != EQUAL)
    {
        printf("%.3lf * x**2 ", a);
    }

    if ((ComparisonOfFractalNumbers(a, 0.0) != EQUAL && ComparisonOfFractalNumbers(b, 0.0) != EQUAL)
    || (ComparisonOfFractalNumbers(a, 0.0) != EQUAL && ComparisonOfFractalNumbers(c, 0.0) != EQUAL))
    {
        printf("+ ");
    }

    if (ComparisonOfFractalNumbers(b, 0.0) != EQUAL)
    {
        printf("%.3lf * x ", b);
    }

    if (ComparisonOfFractalNumbers(b, 0.0) != EQUAL && ComparisonOfFractalNumbers(c, 0.0) != EQUAL)
    {
        printf("+ ");
    }

    if (ComparisonOfFractalNumbers(c, 0.0) != EQUAL
    || (ComparisonOfFractalNumbers(a, 0.0) == EQUAL && ComparisonOfFractalNumbers(b, 0.0) == EQUAL && ComparisonOfFractalNumbers(c, 0.0) == EQUAL))
    {
        printf("%.3lf ", c);
    }

    printf("= 0 ");

}

void PrintValues(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves, const bool visible_values)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (visible_values)
    {
        printf("a = %7.3lf, b = %7.3lf, c = %7.3lf, number_of_solves = %d, x1 = %7.3lf, x2 = %7.3lf\n",
        ptr_args->a, ptr_args->b, ptr_args->c, ptr_solves->number_of_solves, ptr_solves->solve1, ptr_solves->solve2);
    }
}

bool PrintSolve(const TestCase * const ptr_test, const EquationSolves * const ptr_solves, const bool visible_values, const bool false_solve)
{
    assert(ptr_test != NULL);
    assert(ptr_solves != NULL);

    const EquationArgs * const ptr_args = &(ptr_test->args);
    const EquationSolves * const ptr_reference_solves = &(ptr_test->reference_solves);

    if (false_solve)
    {
        ErrorInCalc();

        printf("a = %.3lf, b = %.3lf, c = %.3lf, number_of_solves = %d, x1 = %.3lf, x2 = %.3lf.\n",
        ptr_args->a, ptr_args->b, ptr_args->c, ptr_solves->number_of_solves, ptr_solves->solve1, ptr_solves->solve2);

        printf("number_of_solves_ref = %d, x1_ref = %.3lf, x2_ref = %.3lf\n",
        ptr_reference_solves->number_of_solves, ptr_reference_solves->solve1, ptr_reference_solves->solve2);

        return false;
    }

    else
    {
        PrintValues(ptr_args, ptr_solves, visible_values);
        return true;
    }
}

void PrintErrorValues(const EquationArgs * const ptr_args, const EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);

    ErrorInCalc();
    printf("a = %.3lf, b = %.3lf, c = %.3lf, number_of_solves = %d, x1 = %.3lf, x2 = %.3lf.\n",
    ptr_args->a, ptr_args->b, ptr_args->c, ptr_solves->number_of_solves, ptr_solves->solve1, ptr_solves->solve2);
}

void ErrorInCalc(void)
{
    printf("Произошла ошибка в вычислениях.\n");
}

