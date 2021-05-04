#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <time.h>
#include <functional>
#include <vector>
#include <mutex>
#include <cassert>
// #include "matrix.h"

class Matrix
{
public:
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<double>(c))
    {
    }

    void print()
    {
        for (size_t i = 0; i < rows; ++i)
        {
            std::cout << "| ";
            for (size_t j = 0; j < cols; ++j)
            {
                std::cout << data[i][j];
                if (j != cols-1)
                {
                    std::cout << '\t';
                }
            }

            std::cout << " |\n";
        }
    }

    void init_random()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, 5);
        auto random = std::bind(dist, mt);

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                data[i][j] = random();
            }
        }
    }

    std::vector<double> operator[](size_t i) const
    {
        return data[i];
    }

    std::vector<double>& operator[](size_t i)
    {
        return data[i];
    }

    size_t get_rows() const
    {
        return rows;
    }

    size_t get_cols() const
    {
        return cols;
    }

private:
    size_t rows;
    size_t cols;
    std::vector<std::vector<double>> data;
};

std::mutex mx;

void multiply_thread(Matrix& res, size_t ith, const Matrix& m1, const Matrix& m2)
{
    std::lock_guard<std::mutex> lock(mx);
    const size_t cols1 = m1.get_cols();
    const size_t rows2 = m2.get_rows();

    for (size_t i = 0; i < cols1; ++i)
    {
        for (size_t j = 0; j < rows2; ++j)
        {
            res[ith][i] += m1[ith][j] * m2[j][i];
        }
    }
}

Matrix multiply(const Matrix& m1, const Matrix& m2)
{
    size_t rows1 = m1.get_rows();
    size_t cols2 = m2.get_cols();

    assert(m1.get_cols() == m2.get_rows());

    Matrix res(rows1, cols2);
    std::vector<std::thread> threads(rows1);

    for (size_t i = 0; i < rows1; ++i)
    {
        threads[i] = std::thread(multiply_thread, std::ref(res), i, std::ref(m1), std::ref(m2));
    }

    for (size_t i = 0; i < rows1; ++i)
    {
        threads[i].join();
    }

    return res;
}

int main()
{
    Matrix m1(5, 5);
    m1.init_random();
    std::cout << "first matrix:\n";
    m1.print();
    std::cout << std::endl;

    Matrix m2(5, 5);
    m2.init_random();
    std::cout << "second matrix:\n";
    m2.print();
    std::cout << std::endl;

    Matrix res = multiply(m1, m2);
    std::cout << "result matrix:\n";
    res.print();    

    return 0;
}