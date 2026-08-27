void RunTests(const int number_of_random_tests, const bool visible_values)
{
    if (visible_values)
    {
        printf("\nНачинаю прохождение заданных тестов.\n\n");
    }

    int success_special_tests = RunSpecialTests(visible_values);

    if (visible_values)
    {
        printf("\nНачинаю прохождение рандомных тестов.\n\n");
    }

    int success_random_tests = RunRandomTests(number_of_random_tests, visible_values);

    printf("\nТестирование окончено. Пройдено %d/%zu заданных тестов и %d/%d рандомных тестов.\n",
        success_special_tests, sizeof (SPECIAL_TESTS_VALUES) / sizeof (TestCase), success_random_tests, number_of_random_tests);
}

void RunFileTests(const char * const ptr_name_of_file, const bool visible_values)
{
    assert(ptr_name_of_file != NULL);

    FILE * ptr_test_file = NULL;

    int iteration = 0;
    int success_file_tests = 0;

    ptr_test_file = fopen(ptr_name_of_file, "r");
    assert(ptr_test_file != NULL);

    TestCase test = { };

    while (fscanf(ptr_test_file, "%lf %lf %lf %d %lf %lf", &(test.args.a), &(test.args.b), &(test.args.c),
    &(test.reference_solves.number_of_solves), &(test.reference_solves.solve1), &(test.reference_solves.solve2)) == 6)
    {
        iteration++;

        if (RunOneTest(&test, visible_values))
        {
            success_file_tests++;
        }

        else
        {
            printf("Произошла ошибка в вычислениях на %d тесте.\n", iteration);
        }
    }

    printf("Конец файла. Тестирование окончено. Пройдено %d/%d тестов.\n", success_file_tests, iteration);;
}

int RunSpecialTests(const bool visible_values)
{
    int success_special_tests = 0;

    for (size_t iteration = 0; iteration < sizeof (SPECIAL_TESTS_VALUES) / sizeof (TestCase); iteration++)
    {
        if (RunOneTest(&SPECIAL_TESTS_VALUES[iteration], visible_values))
        {
            success_special_tests++;
        }

        else
        {
            printf("Произошла ошибка в вычислениях на %zu тесте.\n", iteration+1);
        }
    }

    return success_special_tests;
}

int RunRandomTests(const int number_of_random_tests, const bool visible_values)
{
    EquationArgs args = { };
    EquationSolves solves = {.solve1 = NAN, .solve2 = NAN};

    int success_random_tests = 0;

    for (size_t iteration = 0; iteration < size_t (number_of_random_tests); iteration++)
    {
        args = {.a = (RAND_MAX / 2 - rand()) / ACCURACY, .b = (RAND_MAX / 2 - rand()) / ACCURACY, .c = (RAND_MAX / 2 - rand()) / ACCURACY};

        solves = {.solve1 = NAN, .solve2 = NAN};

        if (SolutionsOfEquations(&args, &solves))
        {
            success_random_tests++;
        }

        PrintValues(&args, &solves, visible_values);
    }

    return success_random_tests;
}

bool RunOneTest(const TestCase * const ptr_test, const bool visible_values)
{
    assert(ptr_test != NULL);

    if ((ptr_test->reference_solves).number_of_solves == TWO_SOLVES)
    {
        return CheckTwoSolves(ptr_test, visible_values);
    }

    else if ((ptr_test->reference_solves).number_of_solves == ONE_SOLVE)
    {
        return CheckOneSolve(ptr_test, visible_values);
    }

    else
    {
        return CheckInfOrZeroSolves(ptr_test, visible_values);
    }
}

bool CheckInfOrZeroSolves(const TestCase * const ptr_test, const bool visible_values)
{
    assert(ptr_test != NULL);

    EquationSolves solves = {.solve1 = NAN, .solve2 = NAN};

    SolutionsOfEquations(&(ptr_test->args), &solves);

    bool right_solve = solves.number_of_solves != (ptr_test->reference_solves).number_of_solves;

    return PrintSolve(ptr_test, &solves, visible_values, right_solve);
}

bool CheckTwoSolves(const TestCase * const ptr_test, const bool visible_values)
{
    assert(ptr_test != NULL);

    EquationSolves solves = {.solve1 = NAN, .solve2 = NAN};

    SolutionsOfEquations(&(ptr_test->args), &solves);

    double solve1 = solves.solve1;
    double solve2 = solves.solve2;
    double reference_solve1 = (ptr_test->reference_solves).solve1;
    double reference_solve2 = (ptr_test->reference_solves).solve2;

    SortDoubles(&solve1, &solve2);
    SortDoubles(&reference_solve1, &reference_solve2);

    bool right_solve = solves.number_of_solves != (ptr_test->reference_solves).number_of_solves
    || ComparisonOfFractalNumbers(solve1, reference_solve1) != EQUAL || ComparisonOfFractalNumbers(solve2, reference_solve2) != EQUAL;

    return PrintSolve(ptr_test, &solves, visible_values, right_solve);
}

bool CheckOneSolve(const TestCase * const ptr_test, const bool visible_values)
{
    assert(ptr_test != NULL);

    EquationSolves solves = {.solve1 = NAN, .solve2 = NAN};

    SolutionsOfEquations(&(ptr_test->args), &solves);

    bool right_solve = solves.number_of_solves != (ptr_test->reference_solves).number_of_solves
    || ComparisonOfFractalNumbers(solves.solve1, (ptr_test->reference_solves).solve1) != EQUAL;

    return PrintSolve(ptr_test, &solves, visible_values, right_solve);
}
