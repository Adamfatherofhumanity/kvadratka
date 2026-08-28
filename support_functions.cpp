int ComparisonOfFractalNumbers(const double a, const double b)
{
    if (a - b > EPS)
    {
        return BIGGER;
    }

    else if (a - b < -EPS)
    {
        return SMALLER;
    }

    else
    {
        return EQUAL;
    }
}

void SortDoubles(double * ptr_a, double * ptr_b)
{
    double swap_support = 0;

    if (ComparisonOfFractalNumbers(*ptr_a, *ptr_b) == SMALLER)
    {
        swap_support = *ptr_a;
        *ptr_a = *ptr_b;
        *ptr_b = swap_support;
    }
}

double RandDouble(void)
{
    return (RAND_MAX / 2 - rand()) / ACCURACY;
}

double CalcValueOfQuadraticEq(const EquationArgs * const ptr_args, const double solve)
{
    return ptr_args->a * solve * solve + ptr_args->b * solve + ptr_args->c;
}

void ZeroProblemSolve(EquationSolves * const ptr_solves)
{
    if ((!isnan(ptr_solves->solve1)) && ComparisonOfFractalNumbers(ptr_solves->solve1, 0.0) == EQUAL)
    {
        ptr_solves->solve1 = 0;
    }

    if ((!isnan(ptr_solves->solve2)) && ComparisonOfFractalNumbers(ptr_solves->solve2, 0.0) == EQUAL)
    {
        ptr_solves->solve2 = 0;
    }
}

bool CheckString(void)
{
    int ch = 0;

    while (isspace(ch = getchar()))
    {
        if (ch == '\n')
        {
            return true;
        }
    }

    if (ch != CODE_OF_CTRL_Z && ch != EOF)
    {
        SkipString();
    }

    return false;
}

void SkipString(void)
{
    int ch = 0;

    while ((ch = getchar()) != CODE_OF_CTRL_Z && ch != '\n' && ch != EOF)
    {
        continue;
    }
}
