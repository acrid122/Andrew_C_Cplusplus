#include <stdio.h>
#include <locale.h>
#include <stdarg.h>


int main() {
    setlocale(LC_ALL,"ru-RU.UTF-8");
     struct {
        char name[30];
        int age;
        float grade;
    } student = {"Иван Иванов", 20, 4.5};
    printf("Имя: %s\n", student.name);
    printf("Возраст: %d\n", student.age);
    printf("Оценка: %.2f\n", student.grade);


    struct {
        char name[30];
        int age;
        float grade;
    } student_copy = student;
    printf("Копия - Имя: %s\n", student_copy.name);
    printf("Копия - Возраст: %d\n", student_copy.age);
    printf("Копия - Оценка: %.2f\n", student_copy.grade);
    return 0;
} 