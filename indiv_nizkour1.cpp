#include <iostream>
#include <vector>
#include <omp.h>

// Функция для вычисления определителя матрицы
double determinant(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    double det = 1.0;

    std::vector<std::vector<double>> tempMatrix = matrix;

    // Прямой ход метода Гаусса
    for (int k = 0; k < n; k++) {
#pragma omp parallel for reduction(*:det)
        for (int i = k + 1; i < n; i++) {
            double factor = tempMatrix[i][k] / tempMatrix[k][k];
            for (int j = k; j < n; j++) {
                tempMatrix[i][j] -= factor * tempMatrix[k][j];
            }
        }
    }

    // Вычисление определителя как произведение диагональных элементов
    for (int i = 0; i < n; i++) {
        det *= tempMatrix[i][i];
    }

    return det;
}

int main() {
    // Создание матрицы (пример)
    std::vector<std::vector<double>> matrix = { {2, 3, 4},
                                               {1, 5, 7},
                                               {8, 6, 9} 
                                                };

    // Вычисление определителя
    double det = determinant(matrix);
    std::cout << "Determinant: " << det << std::endl;

    return 0;
}
