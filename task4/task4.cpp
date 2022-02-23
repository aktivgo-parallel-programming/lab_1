﻿#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>

int* create_matrix(int);
void fill_matrix(int*, int, int, int);
void delete_matrix(const int*, int);
void print_matrix(int**, int);
int* multiply_matrix(const int*, const int*, int);
double calculate_multiply_time(int*, int*, int);

const int SIZE = 512;
const int LEFT_BORDER = 0;
const int RIGHT_BORDER = 10;

int main()
{
    srand(time(nullptr));

    int* matrix_1 = create_matrix(SIZE);
    int* matrix_2 = create_matrix(SIZE);
    fill_matrix(matrix_1, SIZE, LEFT_BORDER, RIGHT_BORDER);
    fill_matrix(matrix_2, SIZE, LEFT_BORDER, RIGHT_BORDER);

    /*print_matrix(matrix_1, SIZE);
    std::cout << std::endl;
    print_matrix(matrix_2, SIZE);
    std::cout << std::endl;*/

    double time = calculate_multiply_time(matrix_1, matrix_2, SIZE);
    std::cout << "Time to multiply: " << time << "s" << std::endl;

    delete_matrix(matrix_1, SIZE);
    delete_matrix(matrix_2, SIZE);
}

int* create_matrix(int size)
{
    int* matrix = new int[size * size];

    for (int i = 0; i < size * size; i++) {
        matrix[i] = 0;
    }

    return matrix;
}

void fill_matrix(int* matrix, int size, int left_border, int right_border)
{
    for (int i = 0; i < size * size; i++) {
        matrix[i] = rand() % right_border - left_border;
    }
}

void delete_matrix(const int* matrix, int size)
{
    delete[] matrix;
}

void print_matrix(int* matrix, int size)
{
    for (int i = 0; i < size * size; i++) {
        if (i != 0 && i % size == 0) {
            std::cout << std::endl;
        }
        std::cout << matrix[i] << " ";
    }
}

int* multiply_matrix(const int* matrix_1, const int* matrix_2, int size)
{
    int* result = create_matrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[size * i + j] += matrix_1[size * i + k] * matrix_2[size * k + j];
            }
        }
    }

    return result;
}

double calculate_multiply_time(int* matrix_1, int* matrix_2, int size)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    int* result = multiply_matrix(matrix_1, matrix_2, size);

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

   /* print_matrix(result, size);
    std::cout << std::endl;*/

    return diff.count();
}