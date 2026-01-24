#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define N 15

// Функция бинарного поиска: возвращает индекс элемента или -1, если не найден
// Количество сравнений возвращается через указатель count
int binary_search(int arr[], int size, int target, int *count) {
    int left = 0, right = size - 1;
    *count = 0; // Инициализируем счетчик сравнений

    while (left <= right) {
        int mid = left + (right - left) / 2; // Безопасное вычисление среднего индекса
        (*count)++; // Увеличиваем счетчик за сравнение arr[mid] == target

        if (arr[mid] == target) {
            return mid; // Элемент найден, возвращаем его индекс
        }

        (*count)++; // Увеличиваем счетчик за сравнение arr[mid] < target
        if (arr[mid] < target) {
            left = mid + 1; // Сдвигаем левую границу
        } else {
            right = mid - 1; // Сдвигаем правую границу
        }
    }

    return -1; // Элемент не найден
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int arr[N], target, count;

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Заполнение массива случайными числами от 0 до 99
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    // Сортировка пузырьком
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Вывод массива
    printf("Массив: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Ввод искомого числа
    printf("Искать: ");
    scanf("%d", &target);

    // Выполнение бинарного поиска
    int index = binary_search(arr, N, target, &count);

    // Вывод результата
    if (index != -1) {
        printf("Найдено: значение %d на индексе %d, сравнений: %d\n", arr[index], index, count);
    } else {
        printf("Не найдено: значение %d отсутствует, сравнений: %d\n", target, count);
    }

    return 0;
}
