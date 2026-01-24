#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_PEOPLE 1000
#define PASSING_PLACES 10  // сколько человек проходит (можно менять)

// Структура для хранения человека
typedef struct {
    char name[MAX_NAME];
    int score;
} Person;

void create_file() {
    FILE* file = fopen("results.txt", "w");
    if (!file) {
        printf("Ошибка создания файла!\n");
        return;
    }

    // Пример данных (можно заменить на ввод с клавиатуры)
    fprintf(file, "Иванов Иван 95\n");
    fprintf(file, "Петров Пётр 88\n");
    fprintf(file, "Сидоров Алексей 99\n");
    fprintf(file, "Козлова Анна 92\n");
    fprintf(file, "Морозов Дмитрий 99\n");
    fprintf(file, "Новикова Мария 85\n");
    fprintf(file, "Фёдоров Сергей 97\n");
    fprintf(file, "Волкова Елена 91\n");
    fprintf(file, "Алексеев Михаил 99\n");
    fprintf(file, "Смирнова Ольга 87\n");

    fclose(file);
    printf("Файл results.txt успешно создан!\n");
}

int main() {
    // Шаг 1: Создаём файл с данными
    create_file();

    // Шаг 2: Читаем файл
    FILE* file = fopen("results.txt", "r");
    if (!file) {
        printf("Не удалось открыть файл!\n");
        return 1;
    }

    Person people[MAX_PEOPLE];
    int count = 0;

    while (count < MAX_PEOPLE && 
           fscanf(file, "%s %s %d", 
                  people[count].name, 
                  people[count].name + strlen(people[count].name) + 1, 
                  &people[count].score) == 3) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Файл пустой или ошибка чтения!\n");
        return 1;
    }

    // Шаг 3: Находим максимальный балл
    int max_score = people[0].score;
    for (int i = 1; i < count; i++) {
        if (people[i].score > max_score) {
            max_score = people[i].score;
        }
    }

    // Шаг 4: Сортируем по убыванию баллов (простая сортировка пузырьком)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (people[j].score < people[j + 1].score) {
                Person temp = people[j];
                people[j] = people[j + 1];
                people[j + 1] = temp;
            }
        }
    }

    // Шаг 5: Определяем проходной балл
    int passing_score;
    if (count >= PASSING_PLACES) {
        passing_score = people[PASSING_PLACES - 1].score;
    } else {
        passing_score = people[count - 1].score;  // все проходят
    }

    // Шаг 6: Выводим результаты
    printf("\n=== РЕЗУЛЬТАТЫ ПОСТУПЛЕНИЯ ===\n");
    printf("Всего человек: %d\n", count);
    printf("Мест: %d\n", PASSING_PLACES);
    printf("Максимальный балл: %d\n", max_score);
    printf("Проходной балл: %d\n\n", passing_score);

    printf("Лидеры с максимальным баллом (%d):\n", max_score);
    for (int i = 0; i < count; i++) {
        if (people[i].score == max_score) {
            printf("  - %s %d баллов\n", people[i].name, people[i].score);
        }
    }

    printf("\nПрошли на бюджет (топ-%d):\n", PASSING_PLACES);
    for (int i = 0; i < count && i < PASSING_PLACES; i++) {
        printf("  %d. %s — %d баллов", i + 1, people[i].name, people[i].score);
        if (i == PASSING_PLACES - 1 && count > PASSING_PLACES) {
            printf("  ← Проходной балл");
        }
        printf("\n");
    }

    if (count > PASSING_PLACES) {
        printf("\nНе прошли:\n");
        for (int i = PASSING_PLACES; i < count; i++) {
            printf("  - %s — %d баллов\n", people[i].name, people[i].score);
        }
    }

    return 0;
}