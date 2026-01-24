#include <stdio.h>
#include <locale.h>

#define ROWS 2
#define COLS 3

char *str1 = "Hello World";
char *str2 = "Hello World";

int main(void){
    setlocale(LC_ALL, "ru_RU.UTF-8");


    int matrix[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int trans[COLS][ROWS];

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            trans[j][i] = matrix[i][j];
        }
    };

    for (int i = 0; i < COLS; i++){
        for (int j = 0; j < ROWS; j++){
            printf("%4d", trans[i][j]);
        }
        printf("\n");
    };
    

    /*
      0 1 2       0 1 
    0 1 2 3  -> 0 1 4
    1 4 5 6     1 2 5
                2 3 6
    */


    // Арифметика указателей
    int n = 10;

    int *ptr = &n;
    printf("Адрес=%p \t value = %d \n", (void*)ptr, *ptr);

    //Инкремент указателя
    ptr++;
    printf("Адрес=%p \t value = %d \n", (void*)ptr, *ptr);

    //Декремент
    ptr--;
    printf("Адрес=%p \t value = %d \n", (void*)ptr, *ptr);

    /*
    Увелеичение адреса, который храниится в указателе, на размер типа указателя.
    4 байта. Значит, будет увеличение на 4.
    00000000005FFE0C
    +1
    00000000005FFE0D
    +1
    00000000005FFE0E
    +1
    00000000005FFE0F
    +1
    00000000005FFE10

    Инкремент означает переход к следующему объекту в памяти, а декремент - переход к предыдущему
    */

    double d = 10.6;
    double *pd = &d;

    printf("Адрес=%p \t value = %f \n", (void*)pd, *pd);

    //Инкремент указателя
    pd++;
    printf("Адрес=%p \t value = %f \n", (void*)pd, *pd);

    //Инкремент произошел на 8, так как размер объекта dobule - 8 байт.

    pd = pd + 2;
    printf("Адрес=%p \t value = %f \n", (void*)pd, *pd);

    pd = pd - 3;
    printf("Адрес=%p \t value = %f \n", (void*)pd, *pd);

    //Операция вычитания также может применяться к указателям одного типа

    int a = 10; //00000000005FFDDC
    int b = 23; //00000000005FFDD8
    int *pa = &a;
    int *pb = &b;

    ptrdiff_t c = pa - pb; //расстояние между указателями предстваляет тип ptrdiff_t на 64-разрядной структуре и по факту он является псевдонимом для базового типа long long
    printf("pa = %p \n", (void*)pa);
    printf("pb = %p \n", (void*)pb);
    printf("c = %lld \n", c); //c = 1, так как разница в 4 байта

    int arr[64];
    int *ptr1 = &arr[10];
    int *ptr2 = &arr[40];
    ptrdiff_t dist = ptr2 - ptr1;
    printf("dist = %lld \n", dist);

    int r = 10;
    int *pr = &r;
    int br = *pr + 20; //операция со значением, на который указывает указатель
    pr++; // операция с самим указателем
    printf("br = %d \n", br);

    int t = 10;
    int *pt = &t;
    printf("Адрес=%p \t value = %d \n", (void*)pt, *pt);
    int bt = *pt++; //операции *, ++, -- имеют одинаковые приоритет и при размещении рядом выполняются справа налево.
    /*
    Если сделать (*pt)++, то скобки поменяют порядок операций. Сначала будет выполняться операция разыменования и получение значения, а затем это значение будет
    увеличиваться на 1. Теперь по адресу в указателе будет находится число 11. И из-за того, что инкремент постфиксный, переменная bt получается значение, которое было
    до инкремента, то есть 10.
    */
    /*
    сначала к адресу прибавляется 4, так как тип int, затем т.к. инкремент постфиксный, с помощью операции разыменования возвращается значение, которое было до инкремента - 
    то есть число 10. Это число 10 присваивается перменной bt
    */
    printf("bt: value = %d \n", bt);
    printf("pt: Адрес = %p \t value = %d \n", (void*)pt, *pt);

    //Аналогично будет с префиксным инкрементом bt = ++*pt

    //void - неполный тип, так как компилятор не может узнать его размер.

    int num1 = 11, num2 = 12, num3 = 13, num4 = 14;

    void* p_num = &num1;
    //printf("*p_num: %d \n", *(int*)(p_num + 8)); 
    //результат работы этой строки зависит от конкретного компилятора. GCC/Clang рассматриват void как 1.
    //Формально void остается неполным типом, который не имеет размера.

    //Константы и указатели
    //Можно манипулировать значениями констант через указатели. Несмотря на то, что константы представляют неизменяемые сущности, но указатели позволяют их изменить.

    const int cx = 10;
    //получаем адрес константы, преобразуем в укатаель типа int* и изменяем значение
    *(int*) &cx = 20;
    printf("cx: %d \n", cx);
    //то же самое, только разбито на два этапа
    int* cx_p = &cx;
    *cx_p = 30;
    printf("cx: %d \n", cx);

    const int aa = 10;
    const int *paa = &aa;
    printf("pt: Адрес = %p \t value = %d \n", (void*)paa, *paa);

    int aaa = 10;
    const int *paaa = &aaa;
    printf("value=%d \n", *paaa); //10
    aaa = 22;
    printf("value=%d \n", *paaa); //22
    //*pa = 34 так сделать не получится. 

    //Константые указатели. Они не могут изменять адерс, который в них хранится, но могут изменять значение по этому адресу.

    int aaaa = 10;
    int *const paaaa = &aaaa;
    printf("value=%d \n", *paaaa); //10
    *paaaa = 22;
    printf("value=%d \n", *paaaa); //22

    int baa = 40;
    //paaaa = &baa;
    //Константный указатель на константу
    int ca = 10;
    const int *const pca = &ca;
    //не смогу ни поменять хранимый в указателе адрес, ни значение по этому адресу

    //Указатели на массивы

    //Имя массива без индексов в С является адресом его первого элемента. Соответственно, используя имя массива и индексу элемента, мы можем получить адрес элемента массива

    int numbers[] = {11, 12, 13, 14};
    for(size_t i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++){
        printf("numbers[%d]: %p \n", i, numbers + i);
    }

    printf("numbers[0] = %d \n", *numbers);
    int second = *(numbers + 1);
    printf("numbers[1] = %d \n", second);

    /*
    Более того, когда мы обращаемся к определенному массива, используя квадратные скобки, например numbers[1], то компилятрор рассматривает эту запись
    как прибавление индекса к указателю на начальный элемент: numbers + 1
    */

    int third = 2[numbers];
    printf("numbers[2] = %d \n", third);

    for (int i = 0; i < 4; i++){
        void* address = numbers + i;
        int value = *(numbers + i);
        printf("numbers[%d]: %p, value = %d \n", i, address, value);
    }

    //numbers++ (не смогу так сделать, так как имя массива - нестандартный указатель)
    int* ptr_numbers = numbers;
    printf("value=%d \n", *ptr_numbers); //11

    ptr_numbers = ptr_numbers + 2; //перемещаю указатель на 2 элемента вперед
    printf("value=%d \n", *ptr_numbers);

    *ptr_numbers = 8;
    printf("numbers[2]=%d \n", numbers[2]);

    //Перебор массива с помощью указателей

    //numbers = {11, 12, 8, 14}
    for (int* ptr = numbers; ptr <= &numbers[3]; ptr++){
        printf("pt: Адрес = %p \t value = %d \n", (void*)ptr, *ptr);
    }

    int array[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int nn = sizeof(array) / sizeof(array[0]); // кол-во строк
    int m = sizeof(array[0]) / sizeof(array[0][0]); //кол-во столбцов

    int *final = array[0] + nn * m - 1; //указатель на последний элемент
    for(int* ptr = array[0], i = 1; ptr <= final; ptr++, i++){
        printf("%d \t", *ptr);
        //переход на новую строку
        if (i % m == 0){
            printf("\n");
        }
    }

    //Могли сделать и без указателя на последний элемент, проверяя значение счетчика, пока оно не станет равно общему количеству элементов (m * nn)

    for(int* ptr = array[0], i = 0; i < m * nn;){
        printf("%d \t", *ptr++);
        //переход на новую строку
        if (++i % m == 0){
            printf("\n");
        }
    }

    //Указатели и строки
    char hello[] = "Hello"; //{'H', 'e', 'l', 'l', 'o' ,'\0'}

    char h[4] = "hhh"; //{'h', 'h', 'h', '\0'}
    char h1[3] = "hhh"; //{'h', 'h', 'h'}
    char h2[5] = "hhh"; //{'h', 'h', 'h', '\0', '\0'}

    //Указатели на char
    char *hl = "Hello"; //указатель на char - фактически строка
    printf("%s \n", hl);

    //Интернирование строк позволяет избежать дублирования строк для более эффектинвого использование памяти. Причем здесь неважно, что переменные являются глобальными.
    //Они также могут быть локальными, но все равно будут указывать на один и тот же адрес.

    printf("str1 = %p \n", &str1[0]);
    printf("str2 = %p \n", &str2[0]);

    char *str3 = "Hello World!";
    char *str4 = "Hello World!";
    printf("str1 = %p \n", &str3[0]);
    printf("str2 = %p \n", &str4[0]);

    //Можно получить адрес, по которому располагается строка

    char (*str5)[] = &"Hello World!"; //указатель на массив символов
    printf("str5 = %p \n", str5);

    //строки сохраняются в виде строковых литералов в специальную секцию .rodata (read-only data), которые предназначены только для чтения, а строковые литералы
    //рассматриваются как неизменяемые данные

    //Изменение строк
    char *text = "Hell";
    //Segmentation fault text[1] = 'a'; 
    printf("Новый текст: %s \n", text);

    //*text = 'a'; тоже будет ошибка

    char t1[] = "Hello";
    t1[1] = 'a';
    *t1 = 'B';
    *(t1 + 2) = 'b';
    printf("%s \n", t1);
    return 0;
}