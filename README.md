# parallel-programming-labs
Лабораторные по параллельному программированию ИБАС 4 семестр
# Анализ производительности: Время выполнения vs Размер матрицы

!(graph.png)

## Данные измерений

cores = 1
Matrix size = 200
Execution time(microseconds): 0.00628989
Matrix size = 400
Execution time(microseconds): 0.042888
Matrix size = 800
Execution time(microseconds): 0.431797
Matrix size = 1200
Execution time(microseconds): 1.62047
Matrix size = 1600
Execution time(microseconds): 4.22878
Matrix size = 2000
Execution time(microseconds): 8.69283

cores = 2
Matrix size = 200
Execution time(microseconds): 0.00245141
Matrix size = 400
Execution time(microseconds): 0.0204311
Matrix size = 800
Execution time(microseconds): 0.228098
Matrix size = 1200
Execution time(microseconds): 0.985725
Matrix size = 1600
Execution time(microseconds): 2.5136
Matrix size = 2000
Execution time(microseconds): 5.39058

cores = 4
Matrix size = 200
Execution time(microseconds): 0.00194994
Matrix size = 400
Execution time(microseconds): 0.0133579
Matrix size = 800
Execution time(microseconds): 0.139995
Matrix size = 1200
Execution time(microseconds): 0.765597
Matrix size = 1600
Execution time(microseconds): 1.48156
Matrix size = 2000
Execution time(microseconds): 3.11723

cores = 6
Matrix size = 200
Execution time(microseconds): 0.000881664
Matrix size = 400
Execution time(microseconds): 0.0122257
Matrix size = 800
Execution time(microseconds): 0.0875464
Matrix size = 1200
Execution time(microseconds): 0.538182
Matrix size = 1600
Execution time(microseconds): 1.29034
Matrix size = 2000
Execution time(microseconds): 2.53123

## Вывод

Параметры компиляции  mpic++ -O3 -o matmul main.cpp
Параметры запуска  mprirun -n (cores) ./matmul
При увеличивании количества ядер скорость выполнения программы существенно возрастает
Наибольшая разница наблюдается на матрицах больших размеров