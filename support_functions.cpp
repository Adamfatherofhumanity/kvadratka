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

bool CheckEquationErrors(void)
{
    return (ERROR_EOF == -1 && ERROR_A == 0 && ERROR_B == 1 && ERROR_C == 2 && NO_ERRORS == 3 && ERROR_SO_MANY == 4 && UNEXPECTED_ERROR == 5);
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
