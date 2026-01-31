#include <stdio.h>
#include <stdlib.h>

struct person
{
    char name[16];
    int age;
};

int save(char * filename, struct person *p);
int load(char * filename);

int save_array(char * filename, struct person *p, int n);
int load_array(char * filename);

int main(void){
    /*
    Для записи в файл применяется функция putc, которая имеет следующий прототип;
    int putc(int c, FILE *stream);
    В качестве парамтеров в функцию передаются указатель на файловый поток и символ, который надо записать. Результатом функции
    является записанный символ.
    */

    char message[] = "Hello, world!";

    char * filename = "data11.txt";

    int n = sizeof(message) / sizeof(message[0]);

    FILE * fp = fopen(filename, "w");

    if (fp){
        for(int i = 0; i < n; i++){
            putc(message[i], fp);
        }

        fclose(fp);
    }

    /*
    int getc(FILE *stream);
    для чтения одного символа.
    В качестве параметра в функцию передается указатель на поток, а возвращаемым значением является считанный из файла символ, точнее
    его числовый код
    */

    char c;
    FILE * fp1 = fopen(filename, "r");
    if (fp1)
    {
        //считываем посимвольно

        while((c=getc(fp1)) != EOF)
        {
            printf("%c", c);
        }
        fclose(fp1);
    }

    char * filename1 = "person.dat";
    struct person tom = {"Tom Holland", 20};
    save(filename1, &tom);
    load(filename1);

    char * filename2 = "person_array.dat";
    struct person people[] = { {"Tom", 23}, {"Gennady", 22}, {"Andrew", 18}};
    int k = sizeof(people) / sizeof(people[0]);

    save_array(filename2, people, k);
    load_array(filename2);

    /*
    fwrite преднзначена для записи данных из массива
    size_t fwrite(const void *buffer, size_t size, size_t count, FILE * stream)

    Параметр:
    buffer - указатель на первый объект из массива, который должен быть записан
    size - размер каждого объекта
    count - количество объектов, которые надо записать
    stream - указатель на файловый поток для записи

    В качестве результата функция возвращает количество записанных объектов
    */

    char str[] = "Hello, dear Andrew";
    size_t N = sizeof(str);
    FILE *fp2 = fopen("data_2.txt", "w");
    size_t count = fwrite(str, sizeof str[0], N, fp2);
    printf("wrote %zu elements out of %zu\n", count, N);
    fclose(fp2);
    return 0;
}

//запись в файл
int save(char * filename, struct person *p){
    FILE * fp;
    char * c;
    int size = sizeof(struct person); //количество записываемых байтов
    fp = fopen(filename, "wb"); // открываем файл для бинарной записи
    if (!fp)
    {
        printf("Error occures while opening file \n");
        return 1;
    }
    //устанавливаем указатель на начало структуры
    c = (char *)p;
    for(int i = 0; i < size; i++){
        putc(*c++, fp);
    }
    fclose(fp);
    return 0;
}

int load(char * filename)
{
    FILE * fp;
    char *c;
    int i; //для считывания одного символа
    int size = sizeof(struct person);
    //выделить память для считываемой структуры
    struct person * ptr = malloc(size);
    fp = fopen(filename, "rb"); //бинарное чтение
    if (!fp)
    {
        printf("Error occures while opening file \n");
        return 1;
    }

    c = (char *)ptr;
    while((i=getc(fp)) != EOF){
        *c = i;
        c++;
    }
    fclose(fp);
    //вывод в консоль загруженной структуры
    printf("%-20s %5d \n", ptr->name, ptr->age);
    free(ptr);
    return 0;
}

//запись в файл массива структур
int save_array(char * filename, struct person *p, int n){
    char *c; //для записи отдельных символов
    int size = n * sizeof(struct person);
    FILE * fp = fopen(filename, "wb"); // открываем файл для бинарной записи
    if (!fp)
    {
        printf("Error occures while opening file \n");
        return 1;
    }
    //записываем количество структур
    c = (char *)&n;
    for(int i = 0; i < sizeof(n); i++){
        putc(*c++, fp);
    }

    c = (char *)p;
    for(int i = 0; i < size; i++){
        putc(*c, fp);
        c++;
    }
    fclose(fp);
    return 0;
}

//загрузка из файла массива структур

int load_array(char * filename){
    char * c; //для считывания отдельных символов
    int m = sizeof(int); //сколько надо считать для получения размера массива
    int n; //количество структур в файле

    FILE *fp  = fopen(filename, "r");
    if (!fp)
    {
        printf("Error occures while opening file \n");
        return 1;
    }

    //выделяем память для хранения количества данных
    int *ptr_count = malloc(m);
    //считываем количество структур
    c = (char *)ptr_count;
    //пока не считаем m байт, сохраняем байт в выделенный блок для размера массива
    while (m > 0 && (*c =getc(fp)) != EOF)
    {
        c++;
        m--;
    }

    //получаем число элементов
    n = *ptr_count;
    free(ptr_count);

    //выделяем память для считанного массива структур

    struct person * ptr = malloc(n * sizeof(struct person));

    //устанавливаем указатель на блок памяти, выделенный для массива структур
    c = (char *)ptr;
    while((*c = getc(fp)) != EOF)
    {
        c++;
    }

    printf("\n Found %d people \n\n", n);
    for (int i = 0; i < n; i++){
        printf("%-5d %-10s %5d \n", i + 1, (ptr + i)->name, (ptr + i)->age);
    }
    free(ptr);
    fclose(fp);
    return 0;
}