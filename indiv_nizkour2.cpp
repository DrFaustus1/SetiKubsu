#include <mpi.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

// Функция для генерации последовательной матрицы
void generateMatrix(vector<double>& matrix, int n) {
    srand(time(0));
    for (int i = 0; i < n * n; ++i) {
        matrix[i] = static_cast<double>(rand()) / RAND_MAX;
    }
}

// Функция для вывода матрицы
void printMatrix(const vector<double>& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i * n + j] << " ";
        }
        cout << endl;
    }
}

// Основная функция
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;
    vector<double> matrix;
    vector<double> local_matrix;

    if (rank == 0) {
        cout << "Enter the size of the matrix (n): ";
        cin >> n;
        matrix.resize(n * n);
        generateMatrix(matrix, n);
        cout << "Original matrix:" << endl;
        printMatrix(matrix, n);
    }

    // Передача размера матрицы всем процессам
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Изменение размера локальной матрицы шоб хранениь блок строк, обрабатываемый каждым процессом
    local_matrix.resize(n * (n / size));

    // Распределяем строки матрицы между всеми процессами
    MPI_Scatter(matrix.data(), n * (n / size), MPI_DOUBLE, local_matrix.data(), n * (n / size), MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Локальная транспозиция
    vector<double> local_transpose(n * (n / size));
    for (int i = 0; i < n / size; ++i) {
        for (int j = 0; j < n; ++j) {
            local_transpose[j * (n / size) + i] = local_matrix[i * n + j];
        }
    }

    // Сборка транспонированных блоков обратно в корневой процесс
    MPI_Gather(local_transpose.data(), n * (n / size), MPI_DOUBLE, matrix.data(), n * (n / size), MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Транспонирование собранных блоков для получения окончательной транспонированной матрицы
        vector<double> final_transpose(n * n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                final_transpose[j * n + i] = matrix[i * n + j];
            }
        }
        cout << "Transposed matrix:" << endl;
        printMatrix(final_transpose, n);
    }

    MPI_Finalize();
    return 0;
}
