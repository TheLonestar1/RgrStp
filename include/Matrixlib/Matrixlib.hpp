template <typename T>
class Matrix
{
private:
    size_t rows;
    size_t cols;
    T** data;

public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
    {
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i)
        {
            data[i] = new T[cols];
            memset(data[i], 0, sizeof(T) * cols);
        }
    }

    ~Matrix()
    {
        for (size_t i = 0; i < rows; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }

    class Row
    {
    private:
        T* row_data;
        size_t cols;
    public:
        Row(T* row_data, size_t cols) : row_data(row_data), cols(cols) {}

        T& operator[](size_t col)
        {
            if (col >= cols)
            {
                throw std::out_of_range("Column index out of range");
            }
            return row_data[col];
        }

        const T& operator[](size_t col) const
        {
            if (col >= cols)
            {
                throw std::out_of_range("Column index out of range");
            }
            return row_data[col];
        }

    
    };

    Row operator[](size_t row)
    {
        if (row >= rows)
        {
            throw std::out_of_range("Row index out of range");
        }
        return Row(data[row], cols);
    }

    const Row operator[](size_t row) const
    {
        if (row >= rows)
        {
            throw std::out_of_range("Row index out of range");
        }
        return Row(data[row], cols);
    }

    class Iterator
    {
    private:
        T** ptr;
        size_t row;
        size_t col;
        size_t num_rows;
        size_t num_cols;

    public:
        Iterator(T** ptr, size_t row, size_t col, size_t num_rows, size_t num_cols) :
            ptr(ptr), row(row), col(col), num_rows(num_rows), num_cols(num_cols) {}
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        Iterator& operator++()
        {
            ++col;
            if (col >= num_cols)
            {
                ++row;
                col = 0;
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const
        {
            return ptr == other.ptr && row == other.row && col == other.col;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

        T& operator*() const
        {
            return ptr[row][col];
        }

        T* operator->() const
        {
            return &ptr[row][col];
        }

        bool is_end() const
        {
            return row >= num_rows;
        }
    };

    Iterator begin() { return Iterator(data, 0, 0, rows,cols); }
    Iterator end() { return Iterator(data, rows - 1, cols - 1, rows,cols); }

    Matrix<T> operator+(const Matrix<T>& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result[i][j] = data[i][j] + other[i][j];
            }
        }
        return result;
    }

    // умножение матриц
    Matrix<T> operator*(const Matrix<T>& other) const
    {
        if (cols != other.rows)
        {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        Matrix<T> result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < other.cols; ++j)
            {
                T sum = 0;
                for (size_t k = 0; k < cols; ++k)
                {
                    sum += data[i][k] * other[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    // вычитание матриц
    Matrix<T> operator-(const Matrix<T>& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result[i][j] = data[i][j] - other[i][j];
            }
        }
        return result;
    }

    // деление матриц
    Matrix<T> operator/(const Matrix<T>& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result[i][j] = data[i][j] / other[i][j];
            }
        }
        return result;
    }

    Matrix<T> transpose() const
    {
        Matrix<T> result(cols, rows);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result[j][i] = data[i][j];
            }
        }
        return result;
    }
    Matrix<T>& operator=(const Matrix<T>& other)
    {
        // Проверяем, что это не та же самая матрица
        if (this == &other) {
            return *this;
        }

        // Освобождаем ресурсы текущей матрицы
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;

        // Копируем размеры матрицы и выделяем память
        rows = other.rows;
        cols = other.cols;
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }

        // Копируем элементы матрицы
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }

        return *this;
    }
};
