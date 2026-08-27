bool SolutionsOfEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (ComparisonOfFractalNumbers(ptr_args->a, 0.0) == EQUAL)
    {
        return SolutionsOfLinealEquations(ptr_args, ptr_solves);
    }

    else
    {
        return SolutionsOfQuadraticEquations(ptr_args, ptr_solves);
    }
}

bool SolutionsOfQuadraticEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double discriminant = ptr_args->b * ptr_args->b - 4 * ptr_args->a * ptr_args->c;

    if (ComparisonOfFractalNumbers(discriminant, 0.0) == EQUAL)
    {
        ptr_solves->solve1 = (-ptr_args->b) / (2 * ptr_args->a);
        ptr_solves->number_of_solves = ONE_SOLVE;

        return CheckOneRoot(ptr_args, ptr_solves);
    }

    else if (discriminant < 0)
    {
        ptr_solves->number_of_solves = ZERO_SOLVES;
        return true;
    }

    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        ptr_solves->solve1 = (-ptr_args->b - sqrt_discriminant) / (2 * ptr_args->a);
        ptr_solves->solve2 = (-ptr_args->b + sqrt_discriminant) / (2 * ptr_args->a);
        ptr_solves->number_of_solves = TWO_SOLVES;

        return CheckTwoRoots(ptr_args, ptr_solves);
    }
}

bool SolutionsOfLinealEquations(const struct EquationArgs * const ptr_args, struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    if (ComparisonOfFractalNumbers(ptr_args->b, 0.0) == EQUAL)
    {
        if (ComparisonOfFractalNumbers(ptr_args->c, 0.0) == EQUAL)
        {
            ptr_solves->number_of_solves = INF_SOLVES;
            return true;
        }

        else
        {
            ptr_solves->number_of_solves = ZERO_SOLVES;
            return true;
        }
    }

    else
    {
        ptr_solves->solve1 = (-ptr_args->c) / ptr_args->b;
        ptr_solves->number_of_solves = ONE_SOLVE;

        return CheckOneRoot(ptr_args, ptr_solves);
    }
}

bool CheckTwoRoots(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double value1 = ptr_args->a * ptr_solves->solve1 * ptr_solves->solve1 + ptr_args->b * ptr_solves->solve1 + ptr_args->c;
    double value2 = ptr_args->a * ptr_solves->solve2 * ptr_solves->solve2 + ptr_args->b * ptr_solves->solve2 + ptr_args->c;

    if (ComparisonOfFractalNumbers(value1, 0.0) != EQUAL || ComparisonOfFractalNumbers(value2, 0.0) != EQUAL)
    {
        PrintErrorValues(ptr_args, ptr_solves);
        return false;
    }

    return true;
}

bool CheckOneRoot(const struct EquationArgs * const ptr_args, const struct EquationSolves * const ptr_solves)
{
    assert(ptr_args != NULL);
    assert(ptr_solves != NULL);

    double value = ptr_args->a * ptr_solves->solve1 * ptr_solves->solve1 + ptr_args->b * ptr_solves->solve1 + ptr_args->c;

    if (ComparisonOfFractalNumbers(value, 0.0) != EQUAL)
    {
        PrintErrorValues(ptr_args, ptr_solves);
        return false;
    }

    return true;
}
