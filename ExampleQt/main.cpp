// MatrixLab.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <stdio.h>

double* SolveSLAU(double** matrix, int rowCount, int columnCount)
{
    if (columnCount != rowCount + 1)
    {
        return NULL;
    }
    double ** matrixCopy = new double*[rowCount];

    for (int i = 0; i < rowCount; i++)
    {
        matrixCopy[i] = new double[columnCount];

        for (int j = 0; j < columnCount; j++)
        {
            matrixCopy[i][j] = matrix[i][j];
        }
    }

    double reverseBuffer = 0;
    double determinant = 1;
    for (int i = 0, j = 0; i < (rowCount - 1) && j < (columnCount - 1); i++, j++)
    {
        for (int k = i + 1; k < rowCount; k++)
        {
            if (0 == matrixCopy[i][j])
            {
                for (int l = j; l < columnCount; l++)
                {
                    reverseBuffer = matrixCopy[i][l];
                    matrixCopy[i][l] = matrixCopy[k][l];
                    matrixCopy[k][l] = reverseBuffer;
                }
                determinant *= -1;
            }
            else
            {
                break;
            }
        }

        for (int k = i+1; k < rowCount; k++)
        {
            if (0==matrixCopy[i][j])
            {
                for (i = 0; i < rowCount; i++)
                {
                    delete matrixCopy[i];
                }

                delete matrixCopy;

                return NULL;
            }

            reverseBuffer = -matrixCopy[k][j] / matrixCopy[i][j];

            for (int l = j; l < columnCount; l++)
            {
                matrixCopy[k][l] += matrixCopy[i][l] * reverseBuffer;
            }


        }

    }

    for (int i = 0; i < rowCount; i++)
    {
        determinant *= (double)matrixCopy[i][i];
    }

    if (0 == determinant)
    {
        for (int i = 0; i < rowCount; i++)
        {
            delete matrixCopy[i];
        }

        delete matrixCopy;

        return NULL;
    }

    double* result = new double[rowCount];

    for (int i = rowCount - 1; i >= 0; i--)
    {
        result[i] = matrixCopy[i][columnCount - 1] / matrixCopy[i][i];
        if (i != (rowCount - 1))
        {
            for (int j = i + 1; j <= (columnCount - 2); j++)
            {
                result[i] -= matrixCopy[i][j] * result[j] / matrixCopy[i][i];

            }
        }


    }

    for (int i = 0; i < rowCount; i++)
    {
        delete matrixCopy[i];
    }

    delete matrixCopy;

    return result;
}
#define rows 3
#define columns 4
int main()
{
    double matrix[rows][columns] = { {3,1,-1,-8},{5,8,1,2},{3,-2,6,-7} };

    double** matrixPoint = new double*[rows];
    for (int i = 0; i < rows; i++)

    {
        matrixPoint[i] = new double[columns];
        for (int j = 0; j < columns; j++)
        {
            matrixPoint[i][j] = matrix[i][j];
        }
    }
    double * result = SolveSLAU(matrixPoint, rows, columns);

    for (int i = 0; i < rows; i++)

    {
        delete matrixPoint[i];
    }

    delete matrixPoint;

    for (int i = 0; i < rows; i++)
    {
        printf("%lf ", result[i]);
    }

    delete result;

    return 0;
}

