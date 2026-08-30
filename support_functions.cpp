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

void PlottingTheGraph(const EquationArgs * const ptr_args, ImageModificationParameters * const ptr_pars)
{
    CanvasPreparation(ptr_pars);

    double x_prev = -WIDTH / 2;
    double y_prev = ptr_args->a * x_prev * x_prev + ptr_args->b * x_prev + ptr_args->c;

    for (double x_curr = -WIDTH / 2; x_curr <= WIDTH / 2; x_curr += STEP_X)
    {
        double y_curr = ptr_args->a * x_curr * x_curr + ptr_args->b * x_curr + ptr_args->c;

        txLine (WIDTH / 2 + ptr_pars->scale * x_prev - ptr_pars->x_offset, HEIGHT / 2 - ptr_pars->scale * y_prev + ptr_pars->y_offset,
                WIDTH / 2 + ptr_pars->scale * x_curr - ptr_pars->x_offset, HEIGHT / 2 - ptr_pars->scale * y_curr + ptr_pars->y_offset);

        x_prev = x_curr;
        y_prev = y_curr;
    }
}

void CreatingCanvas(ImageModificationParameters * const ptr_pars)
{
    _txConsole = -1;
    txCreateWindow(WIDTH, HEIGHT);
    ShowWindow(txWindow(), SW_HIDE);
    CanvasPreparation(ptr_pars);
}

void CanvasPreparation(ImageModificationParameters * const ptr_pars)
{
    txClear();
    txSetColor(TX_BLACK, LINE_THICKNESS);
    txLine(0, HEIGHT / 2 + ptr_pars->y_offset, WIDTH, HEIGHT / 2 + ptr_pars->y_offset);
    txLine(WIDTH / 2 - ptr_pars->x_offset, 0, WIDTH / 2 - ptr_pars->x_offset, HEIGHT);
    txSetColor(TX_BLACK, GRAPH_THICKNESS);
}

void ImageModification(const EquationArgs * const ptr_args, ImageModificationParameters * const ptr_pars)
{
    while (!txGetAsyncKeyState(VK_ESCAPE))
    {
        if (txGetAsyncKeyState(VK_UP))
        {
            ptr_pars->y_offset += STEP_X_OR_Y_OFFSET;
            txEnd();
        }

        else if (txGetAsyncKeyState(VK_DOWN))
        {
            ptr_pars->y_offset -= STEP_X_OR_Y_OFFSET;
            txEnd();
        }

        else if (txGetAsyncKeyState(VK_RIGHT))
        {
            ptr_pars->x_offset += STEP_X_OR_Y_OFFSET;
            txEnd();
        }

        else if (txGetAsyncKeyState(VK_LEFT))
        {
            ptr_pars->x_offset -= STEP_X_OR_Y_OFFSET;
            txEnd();
        }

        else if (txGetAsyncKeyState(VK_OEM_PLUS))
        {
            ptr_pars->scale += STEP_SCALE;
            txEnd();
        }

        else if (txGetAsyncKeyState(VK_OEM_MINUS))
        {
            if (ComparisonOfFractalNumbers(ptr_pars->scale, STEP_SCALE) == EQUAL || (ptr_pars->scale -= STEP_SCALE) < 0)
            {
                ptr_pars->scale = STEP_SCALE;
            }
            txEnd();
        }

        PlottingTheGraph(ptr_args, ptr_pars);
        txBegin();
        txSleep();
    }
}
