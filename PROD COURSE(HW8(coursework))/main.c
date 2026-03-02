#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef float (*function)(float);

// переменные для сбора статистики
static int root_iterations = 0;  // кол-во итераций при поиске корня
static int integral_iterations = 0;  // кол-во итераций при вычислении интеграла

// функции
float f1(float x) 
{
    return 0.6f * x + 3.0f;
}

float f2(float x) 
{
    float temp = x - 2.0f;
    return temp * temp * temp - 1.0f;
}

float f3(float x) 
{
    return 3.0f / x;
}

// производные функций
float f1_derivative(float x) 
{
    return 0.6f;  // производная линейной функции
}

float f2_derivative(float x) 
{
    float temp = x - 2.0f;
    return 3.0f * temp * temp;  // производная кубической функции
}

float f3_derivative(float x) 
{
    return -3.0f / (x * x);  // производная функции 3/x
}

// доп. функция поиска корня - разность двух функций
float diff_func(float x, function f, function g) 
{
    return f(x) - g(x);
}

// функция поиска корня методом линейного поиска
float root(function f, function g, float a, float b, float eps1, 
           function fd, function gd) 
{
    root_iterations = 0;
    float step = eps1;
    float min_x = a;
    float min_val = fabs(diff_func(a, f, g));
    float x;
    
    for (x = a; x <= b; x += step) 
    {
        root_iterations++;
        float val = fabs(diff_func(x, f, g));
        if (val < min_val) 
        {
            min_val = val;
            min_x = x;
        }
    }
    return min_x;
}

// функция вычисления интеграла методом трапеций
float integral(function f, float a, float b, float eps2) 
{
    integral_iterations = 0; 
    int n = 1;
    float prev_result = 0.0f;
    float result = 0.0f;
    
    do {
        prev_result = result;
        result = 0.0f;
        float h = (b - a) / n;
        int i;

        // метод трапеций
        result = (f(a) + f(b)) / 2.0f;
        for (i = 1; i < n; i++) {
            integral_iterations++;
            result += f(a + i * h);
        }
        result *= h;
        
        n *= 2;  // удвоение кол-ва разбиений (большая точность)
    } while (fabs(result - prev_result) > eps2 && n < 1000000);
    
    return result;
}

// тестовые функции
float test_square(float x) 
{ 
    return x * x; 
}

float test_const(float x) 
{ 
    return 4.0f; 
}

// тест функций root и integral
void run_tests() 
{
    printf("\n=== TESTING ===\n");
    
    // Тест 1: Поиск корня для простой функции x^2 - 4 = 0 на [1, 3]
    float root1 = root(test_square, test_const, 1.0f, 3.0f, 0.001f, NULL, NULL);
    printf("Root test (x^2 = 4): expected 2.0, got %.3f, iterations: %d\n", 
           root1, root_iterations);
    
    // Тест 2: Интеграл от x^2 на [0, 1] (должен быть 1/3)
    float integral1 = integral(test_square, 0.0f, 1.0f, 0.001f);
    printf("Integral test (x^2 from 0 to 1): expected 0.333, got %.3f, iterations: %d\n", 
           integral1, integral_iterations);
    
    // Тест 3: Проверка точек пересечения
    printf("\nChecking intersection points:\n");
    
    float r13 = root(f1, f3, 0.8f, 1.0f, 0.001f, NULL, NULL);
    printf("f1 and f3 intersection: x = %.3f, f1(x)=%.3f, f3(x)=%.3f\n", 
           r13, f1(r13), f3(r13));
    
    float r12 = root(f1, f2, 3.5f, 4.0f, 0.001f, NULL, NULL);
    printf("f1 and f2 intersection: x = %.3f, f1(x)=%.3f, f2(x)=%.3f\n", 
           r12, f1(r12), f2(r12));
    
    float r23 = root(f2, f3, 3.0f, 3.5f, 0.001f, NULL, NULL);
    printf("f2 and f3 intersection: x = %.3f, f2(x)=%.3f, f3(x)=%.3f\n", 
           r23, f2(r23), f3(r23));
    
    printf("=== TESTING COMPLETE ===\n\n");
}

// справка по использованию программы
void print_help() 
{
    printf("Usage: program [options]\n");
    printf("Options:\n");
    printf("  -help           Print this help message\n");
    printf("  -intersections  Print abscissas of intersection points\n");
    printf("  -iterations     Print number of iterations for root finding\n");
    printf("  -test           Run tests for root and integral functions\n");
    printf("\nThe program calculates the area bounded by three curves:\n");
    printf("  f1(x) = 0.6x + 3\n");
    printf("  f2(x) = (x-2)^3 - 1\n");
    printf("  f3(x) = 3/x\n");
    printf("\nIntersection points:\n");
    printf("  f1 and f3: (0.871, 3.51)\n");
    printf("  f1 and f2: (3.835, 5.27)\n");
    printf("  f2 and f3: (3.283, 0.87)\n");
}

// функции для вычисления площади
float diff_f1_f3(float x) 
{
    return f1(x) - f3(x);
}

float diff_f1_f2(float x) 
{
    return f1(x) - f2(x);
}

int main(int argc, char *argv[]) 
{
    // Флаги для опций командной строки
    int print_intersections = 0;
    int print_iterations = 0;
    int run_test_mode = 0;
    int i;
    
    // Обработка аргументов командной строки
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-intersections") == 0) {
            print_intersections = 1;
        } else if (strcmp(argv[i], "-iterations") == 0) {
            print_iterations = 1;
        } else if (strcmp(argv[i], "-test") == 0) {
            run_test_mode = 1;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            printf("Use -help for usage information\n");
            return 1;
        }
    }
    
    // Запуск тестов, если запрошено
    if (run_test_mode) {
        run_tests();
        return 0;
    }
    
    // Находим точки пересечения функций
    float eps = 0.001f;
    
    // Пересечение f1 и f3 (0.871)
    float x13 = root(f1, f3, 0.8f, 1.0f, eps, f1_derivative, f3_derivative);
    int iter13 = root_iterations;
    
    // Пересечение f1 и f2 (3.835)
    float x12 = root(f1, f2, 3.5f, 4.0f, eps, f1_derivative, f2_derivative);
    int iter12 = root_iterations;
    
    // Пересечение f2 и f3 (3.283)
    float x23 = root(f2, f3, 3.0f, 3.5f, eps, f2_derivative, f3_derivative);
    int iter23 = root_iterations;
    
    // абсциссы точек пересечения
    if (print_intersections) {
        printf("Intersection points abscissas:\n");
        printf("  f1 and f3: x = %.6f\n", x13);
        printf("  f1 and f2: x = %.6f\n", x12);
        printf("  f2 and f3: x = %.6f\n", x23);
    }
    
    // количество итераций
    if (print_iterations) {
        printf("Root finding iterations:\n");
        printf("  f1 and f3: %d iterations\n", iter13);
        printf("  f1 and f2: %d iterations\n", iter12);
        printf("  f2 and f3: %d iterations\n", iter23);
    }
    
    // Вычисление площади
    float area = 0.0f;
    
    // Первый участок: от x13 до x23
    area += integral(diff_f1_f3, x13, x23, eps);
    
    // Второй участок: от x23 до x12
    area += integral(diff_f1_f2, x23, x12, eps);
    
    // Вывод результата
    printf("\nCalculated area: %.6f\n", area);
    
    return 0;
}