void Greetings(void)
{
    printf("Приветствую, пользователь.\nЯ программа, умеющая решать квадратные уравнения.\n"
           "Введи 3 числа (сначала коэффициент при x^2, потом при x, потом свободный): ");
}

void TestModeGreetings(void)
{
    printf("Начинаю unit-тестирование модуля SolutionsOfEquations.\n");
}

void Help(void)
{
    printf("У программы есть 2 режима: тестирование и взаимодействие с пользователем.\n");
    printf("Для режима тестирования надо ввести определённые аргументы в командную строку. Вот пример правильного ввода:\n"
           "name_of_file test number_of_random_tests (по умолчанию 1000, можно задать"
           " своё значение) -v (вывод проверяемых аргументов, без флага не выводятся)\n");
    printf("Также можно подключить тесты из файла, для этого надо ввести флаг -f и написать название файла с тестами (по умолчанию test.txt)\n");
    printf("В остальных случаях запустится режим взаимодействия с пользователем.\n");
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

int ContinueOrStop(bool * ptr_need_to_continue)
{
    assert(ptr_need_to_continue != NULL);

    int answer = 0;

    printf("Хотите продолжить ввод (введите Y если да или N если нет): ");

    while (1)
    {
        while (isspace(answer = getchar()))
        {
            continue;
        }

        if (answer == 'Y')
        {
            if (CheckString())
            {
                printf("Введи 3 числа (сначала коэффициент при x^2, потом при x, потом свободный): ");
                return 0;
            }
        }

        else if (answer == 'N')
        {
            if (CheckString())
            {
                printf("Спасибо, что пользовались моей программой.");
                *ptr_need_to_continue = false;
                return 0;
            }
        }

        InvalidAnswer();
    }
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
        printf("Конец файла.");
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

void PrintEq(const EquationArgs * const ptr_args)
{
    assert(ptr_args != NULL);

    double a = ptr_args->a;
    double b = ptr_args->b;
    double c = ptr_args->c;

    printf("У уравнения ");

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

void InvalidAnswer(void)
{
    printf("Принимаются только ответы Y/N (введите Y если да или N если нет): ");
}

void InvalidCommand(void)
{
    printf("Ошибка в аргументах командной строки. Для получения помощи в использовании программы введите флаг --help при запуске.\n");
}

void ErrorInCalc(void)
{
    printf("Произошла ошибка в вычислениях.\n");
}

