#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Drawing(double *Table, int x, int y);

void Starting_Summing(int x, int y);

int Reading_One_Number();

void Reading(unsigned int *First_Number, unsigned int *Second_Number);

void Reading_Each_Number(double *Number_Inpt, int i, int j);

int Check_String_Empty();

void Clear_Buf();

void Making_Each_Table(double **Table, int x, int y);

void Making_Table(double *Table, int x, int y);

void Making_Table_Of_Games(double *Table, int x, int y);

void Sum_Of_Two_Massives(double *Mas_1, double *Mas_2, double **Mas_3,  int x, int y);

int Is_Close_To_Zero(double Number);

enum All_Possible_Exit_Codes
{
    SOMETHING_WENT_WRONG      = -1,
    PROGRAM_STILL_IN_PROGRESS =  0,
    ALL_FINISHED_SUCCESFULLY  =  1,
};

const double SMALL_DIFF = 1e-6;

int main()
{
    unsigned x = 0;
    unsigned y = 0;
    printf ("Type 1 if you want to make sum of two tables:\n");
    printf ("Type 2 if you want to make table of football games:\n");
    int Type_Of_Program = Reading_One_Number();

    Reading(&x, &y);
    printf("\nx = %d\ty = %d\n", x, y);

    if (Type_Of_Program == 1)
    {
        double *Table_1 = {};
        Making_Each_Table( &Table_1,  x,  y);

        double *Table_2 = {};
        Making_Each_Table( &Table_2,  x,  y);

        double *Table_3 = {};
        Table_3 = (double *)calloc(x*y,  sizeof(double));

        Sum_Of_Two_Massives(Table_1, Table_2, &Table_3,  x, y);


        Drawing(Table_3, x, y);

        free(Table_1);
        free(Table_2);
        free(Table_3);
    }

    else
    {
        double *Table_4;
        Table_4 = (double *)calloc(x*y,  sizeof(double));
        Making_Table_Of_Games(Table_4, x, y);
        Drawing(Table_4, x, y);
        free(Table_4);
    }
    printf("See Ya!");
}



int Reading_One_Number()
{
    while (1)
    {
        int Input_Number = 0;
        int Result_1 = 0;
        int Result_2 = 0;

        Result_1 = scanf("%d", &Input_Number);

        Result_2 = Check_String_Empty();

        if (Result_1 * Result_2 && (Input_Number == 1 || Input_Number == 2) )
        {
            return Input_Number;
            break;
        }

        else
        {
            printf("Wrong number\n");
            Clear_Buf();
        }
    }
}



void Reading(unsigned int *x, unsigned int *y)
{
    assert (*x != NAN);
    assert (isfinite (*x) == 1);
    assert (*y != NAN);
    assert (isfinite (*y) == 1);

    printf("Please print there Length \"X\" and Width \"Y\" of the table\n");

    while (1)
    {
        int x_Pos = 0;
        int y_Pos = 0;

        int Result_1 = 0;
        int Result_2 = 0;

        Result_1 = scanf("%d %d", &x_Pos, &y_Pos);

        Result_2 = Check_String_Empty();

        if (Result_1 * Result_2 && x_Pos > 0 && y_Pos > 0)
        {
            *x = x_Pos;
            *y = y_Pos;
            break;
        }

        else
        {
            printf("Wrong numbers\n");
            Clear_Buf();
        }
    }
}



void Reading_Each_Number(double *Number_Inpt, int i, int j)
{
    while (1)
    {
        printf("[%d] [%d] = ", i, j);

        double Number = 0;

        int Result = scanf("%lg", &Number);

        if (Result)
        {
            printf ("%lg\n", Number);
            *Number_Inpt = Number;
            return;
        }

        else
        {
            printf("Wrong number\n");
            Clear_Buf();
        }
    }
}



int Check_String_Empty()
{
    int Current_Symbol = 1;

    while (Current_Symbol == 1 && Current_Symbol != EOF && Current_Symbol != '\n')
    {
        Current_Symbol = getchar();
        if (isspace(Current_Symbol) == 0)

            return 0;
    }

    return 1;
}



void Clear_Buf()
{
    int Current_Symbol = getchar();

    while (Current_Symbol != EOF && Current_Symbol != '\n')
        Current_Symbol = getchar();
}



void Making_Each_Table(double **Table, int x, int y)
{
    *Table = (double *)calloc(x*y,  sizeof(double));

    Making_Table(*Table, x, y);
}

void Making_Table(double *Table, int x, int y)
{
    assert (x != NAN);
    assert (isfinite (x) == 1);
    assert (y != NAN);
    assert (isfinite (y) == 1);

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y ; j++)
        {

            double Number_Inpt = 0;
            Reading_Each_Number(&Number_Inpt, i, j);
            *(double *)((size_t)Table + x * i * sizeof(double) + j * sizeof(double)) = Number_Inpt;
            //   *((double *)Table + x * i + j) = Number_Inpt;
        }
    }
}



void Making_Table_Of_Games(double *Table, int x, int y)
{
    assert (x != NAN);
    assert (isfinite (x) == 1);
    assert (y != NAN);
    assert (isfinite (y) == 1);

    int Starting_Coefficient = 0;
    for (int i = 0; i < x; i++)
    {

        for (int j = Starting_Coefficient; j < y ; j++)
        {

            double Number_Inpt = 0;
            Reading_Each_Number(&Number_Inpt, i, j);
            *(double *)((size_t)Table + x * i * sizeof(double) + j * sizeof(double)) = Number_Inpt;
            //   *((double *)Table + x * i + j) = Number_Inpt;
        }
        Starting_Coefficient += 1;
    }
}



void Drawing(double *Table, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {

            printf("|");
            double Printing_Num = *(double *)((size_t)Table + x * i * sizeof(double) +
                                                                         j * sizeof(double));
            if (Is_Close_To_Zero(Printing_Num))
                printf("      ");
            else
                printf("%6.2f", Printing_Num);
            printf("|");
        }
        printf("\n");
    }
    printf("\n");
}



void Sum_Of_Two_Massives(double *Mas_1, double *Mas_2, double **Mas_3,  int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y ; j++)
        {
            *(double *)((size_t)*Mas_3 + x * i * sizeof(double) + j * sizeof(double)) =
             *(double *)((size_t)Mas_1 + x * i * sizeof(double) + j * sizeof(double)) +
             *(double *)((size_t)Mas_2 + x * i * sizeof(double) + j * sizeof(double));
        }
    }
}



int Is_Close_To_Zero(double Number)
{
    assert (Number != NAN);
    assert (isfinite (Number) == 1);

    if (fabs(Number) <= SMALL_DIFF)
        return 1;

    return 0;
}
