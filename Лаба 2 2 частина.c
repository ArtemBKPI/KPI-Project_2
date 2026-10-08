
#include <stdio.h>  // Бібліотека для printf і scanf
#include <math.h>   // Бібліотека для atan, fabs, isfinite

// Функція з варіанта 1: f(x) = 1 / (4 + x^2)
double f(double x)
{
    return 1.0 / (4.0 + x * x);
}

// Метод лівих прямокутників
double leftRectangle(int n)
{
    double h = 1.0 / n;   // Крок інтегрування
    double sum = 0.0;     // Початкова сума

    for (int i = 0; i < n; i++)
        sum += f(i * h);   // Ліва точка проміжку

    return sum * h;
}

// Метод правих прямокутників
double rightRectangle(int n)
{
    double h = 1.0 / n;
    double sum = 0.0;

    for (int i = 1; i <= n; i++)
        sum += f(i * h);   // Права точка проміжку

    return sum * h;
}

// Метод середніх прямокутників
double middleRectangle(int n)
{
    double h = 1.0 / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += f((i + 0.5) * h); // Середина проміжку

    return sum * h;
}

// Метод трапецій
double trapezoid(int n)
{
    double h = 1.0 / n;

    // Початкова сума крайніх значень
    double sum = (f(0.0) + f(1.0)) / 2.0;

    for (int i = 1; i < n; i++)
        sum += f(i * h);

    return sum * h;
}

// Метод Сімпсона
// Кількість проміжків n повинна бути парною
double simpson(int n)
{
    double h = 1.0 / n;
    double sum = f(0.0) + f(1.0);

    for (int i = 1; i < n; i++)
    {
        if (i % 2 == 0)
            sum += 2.0 * f(i * h);
        else
            sum += 4.0 * f(i * h);
    }

    return sum * h / 3.0;
}

// Вибір методу обчислення
double calculate(int method, int n)
{
    if (method == 1) return leftRectangle(n);
    if (method == 2) return rightRectangle(n);
    if (method == 3) return middleRectangle(n);
    if (method == 4) return trapezoid(n);

    return simpson(n);
}

// Пошук кількості проміжків для заданої похибки
int findIntervals(int method, double exact, double eps)
{
    // Для Сімпсона починаємо з 2 проміжків
    int n = (method == 5) ? 2 : 1;

    // Поки похибка більша за допустиму
    while (fabs(calculate(method, n) - exact) > eps)
    {
        // Захист від дуже великої кількості проміжків
        if (n >= 1048576)
            return -1;

        // Збільшуємо кількість проміжків удвічі
        n *= 2;
    }

    return n;
}

int main(void)
{
    int n;       // Кількість проміжків
    double eps;  // Допустима похибка

    // Назви методів
    const char *names[5] = {
        "Left rectangles",
        "Right rectangles",
        "Middle rectangles",
        "Trapezoids",
        "Simpson"
    };

    // Введення кількості проміжків
    printf("Enter number of intervals n: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000000)
    {
        printf("Error: incorrect n!\n");
        return 1;
    }

    // Введення допустимої похибки
    printf("Enter allowed error eps: ");
    if (scanf("%lf", &eps) != 1 || !isfinite(eps) || eps <= 0.0)
    {
        printf("Error: incorrect eps!\n");
        return 1;
    }

    // Точне значення інтеграла
    double exact = atan(0.5) / 2.0;

    printf("\nExact integral = %.12f\n", exact);

    // Заголовок таблиці
    printf("\n%-22s %9s %18s %16s\n",
           "Method", "n", "Integral", "Absolute error");

    // Обчислення всіма п'ятьма методами
    for (int method = 1; method <= 5; method++)
    {
        int usedN = n;

        // Для Сімпсона n повинно бути парним
        if (method == 5 && usedN % 2 != 0)
            usedN++;

        // Обчислюємо інтеграл
        double value = calculate(method, usedN);

        // Знаходимо абсолютну похибку
        double error = fabs(value - exact);

        // Виводимо результат
        printf("%-22s %9d %18.12f %16.8e\n",
               names[method - 1], usedN, value, error);
    }

    // Пошук кількості проміжків за похибкою
    printf("\nIntervals needed for error <= %.8g:\n", eps);

    for (int method = 1; method <= 5; method++)
    {
        int needed = findIntervals(method, exact, eps);

        if (needed == -1)
        {
            printf("%-22s Not found within the limit\n",
                   names[method - 1]);
        }
        else
        {
            // Похибка для знайденої кількості проміжків
            double error = fabs(
                calculate(method, needed) - exact
            );

            printf("%-22s n = %d, error = %.8e\n",
                   names[method - 1], needed, error);
        }
    }

    return 0; // Успішне завершення програми
}
