#include <gtest/gtest.h>
#include <Matrixlib/Matrixlib.hpp>

TEST(MatrixTest, CreateEmptyMatrix)
{
    Matrix<int> mat(1,1);

    EXPECT_EQ(mat.get_cols(), 1);
    EXPECT_EQ(mat.get_rows(), 1);
}

TEST(MatrixTest, FillAndGetMatrixData)
{
    const int numRows = 3, numCols = 2;
    Matrix<double> mat(numRows, numCols);
    for (auto& x : mat)
    {
        x = rand() % 6;
    }
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            double value = mat[i][j];
            EXPECT_EQ(value, mat[i][j]);
        }
    }
}
