
#include <iostream>
#include <omp.h>
using namespace std;
double f(double x) {
    //функция которую будем интегрировать
    return x * x;
}

double trapezoidal_integration(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

#pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

int main() {
    setlocale(LC_ALL, "rus");
    double a = 0.0;
    double b = 1.0;
    int n = 1000; // Количество разбиений

    double result = trapezoidal_integration(a, b, n);
    cout << "Результат интегрирования: " << result << std::endl;

    return 0;
}
