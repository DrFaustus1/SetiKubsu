#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_NUMBER_COUNT 1000

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cout << "Должно быть как минимум 2 процесса для работы программы." << std::endl;
        MPI_Finalize();
        return 1;
    }

    // Имена исходных файлов
    std::string filenames[] = { "file1.txt", "file2.txt", "file3.txt" };

    // Создание имени выходного файла
    std::string output_filenames[3];
    for (int i = 0; i < 3; i++) {
        output_filenames[i] = filenames[i] + "_res";
    }

    // Чтение и обработка данных
    std::ifstream input_file(filenames[rank - 1]);
    std::ofstream output_file(output_filenames[rank - 1]);

    double numbers[MAX_NUMBER_COUNT];
    int count = 0;

    double number;
    while (input_file >> number) {
        int int_part = static_cast<int>(number);
        numbers[count] = int_part;
        count++;
    }

    for (int i = 0; i < count; i++) {
        output_file << numbers[i] << std::endl;
    }

    input_file.close();
    output_file.close();

    MPI_Finalize();
    return 0;
}
