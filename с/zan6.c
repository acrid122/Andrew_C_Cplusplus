#include <stdio.h>
#include <locale.h>

int kk = 100; //глобальная переменная
extern char message1[]; //переменная message1 из файла zan6_second.c
/*
если перменная определена во внешнем файле, то перед ее использованием должно идти ее описание с ключевым словом extern. При описании не присваиваем значение.
если мы хотим использовать внешние функции, то перед их использованием надо определить прототип.
*/
void print_zan6_second();
int difference(int, int);
//функция multiply_numbers доступна не будет, так как она static (а значит, мы не можем ее использовать во внешних файлах)


void hello()
{
    printf("Hello! \n");
}

//описание
void hello1();
void print_message(char[]);
void sum_numbers(int, int);
void increase_number(int);
void change_number(const int);
int sum_numbers_1(int, int);
int calculate(int, int, char);
int factorial(int);
void print_n();
void print_static_variable();

int main(void){
    //Массивы указателей, многоуровневая адресация

    /*
    тип *имя_массива [размер]
    тип *имя_массива [] = инициализатор
    тип *имя_массива [размер] = инициализатор
    */
   int array[] = {1, 2, 3, 4};
   int *p1[4];
   int *p2[] = {&array[1], &array[2], &array[3]};
   int *p3[4] = {&array[1], &array[2], &array[3]};

   for(int i = 0; i < 3; i++){
    printf("%d \n", *p2[i]); //printf("%d \n", **(p2 + i))
   }

   int(*pa)[4] = &array;
   //тип_элементов_массива (*имя_переменной_указателя)[количество элементов]
   //int(*pb)[3] = &array;
   /*
   c:\Users\Gennady\Desktop\Andrew Purshev\zan6.c:21:18: error: initialization of 'int (*)[3]' from incompatible pointer type 'int (*)[4]' [-Wincompatible-pointer-types]
   21 |    int(*pb)[3] = &array;
   */
   int(*pb)[] = &array;
   printf("array[0] = %d \n", (*pb)[0]);
   printf("array[1] = %d \n", (*pb)[1]);
   printf("array[2] = %d \n", (*pb)[2]);
   printf("array[3] = %d \n", (*pb)[3]);
   
   int array2[3][2] = {{11, 12}, {13, 14}, {15, 16}};
   int (*pc)[2] = array2 + 1;

   for(size_t i = 0; i < sizeof(*pa)/sizeof(*pa[0]); i++){
    printf("%d, ", (*pc)[i]);
   }

   //Многоуровневая адресация - указатель на указатель, на указатель ... на указатель, который хранит адрес элемента
   int x = 2;
   int *px = &x; //указатель px хранит адрес переменной x
   int **ppx = &px; //указатель ppx хранит адрес указателя px
   printf("Address px: %p \n", (void *)ppx);
   printf("Address x: %p \n", (void *)*ppx);
   printf("x: %d \n", **ppx);

   /*
   тип имя_функции(параметры){
   выполняемые_инструкции
   }

   если функция не возвращает никакого значения, то используется тип void (процедура)

   вызов функции осуществляется в форме имя_функции(аргументы). компилятор должен знать о функции до ее вызова.
   описание функции - прототип. формальное опередление прототипа: тип имя_функции(параметры)
   
   тип имя_функции(тип параметр1, тип параметр2 ...).

   Между передаваемыми в функцию аргументами и ее параметрами должно быть соотвествие по типу. Если же типы не совпадают, то компилятор пытается автоматически выполнить
   преобразование типов.

   при компиляции функции для ее параметров выделяются отдельные участки памяти. при этом для параметров типа float формируются в памяти объекты типа double,
   а для параметров char, short int - объекты типа int.

   после заверешения работы функции память, выделенная для параметров, освобождается.

   как может выглядеть return?
   return;
   return выражение;

   Локальные переменные - переменные, которые определяются внутри какого-то блока кода, например, функции и существуют только в рамках этого блока. Характеризуются автоматическим
   временем жизни: при входе в блок для этих переменных выделяется память, а после завершения работы этого блока, выделенная память освобождается, а объекты удаляются.

   Глобальные переменные - переменные, которые определены в файле программы вне какой-то функции.

   Статические переменные. Они определяются на уровне функций при помощи ключевого слова static. Если автоматические переменные определяются и инициализируются при каждом входе в 
   функцию, то статические переменные инициализируются только один раз, а при последующих вызовах функции используется старое значение статической переменной. Статические переменные видны исключительно
   внутри того файла, где они объявлены
   */
   hello();
   hello();
   hello1();
   print_message("Hello, world");
   print_message("Hello, Andrew");
   sum_numbers(1, 2);
   sum_numbers(1.5, 2.5);
   int a = 10;
   int b = 20;
   sum_numbers(a, b); //идет передача по значению. то есть функция не изменяет значения передаваемых аргументов.
   increase_number(a);
   printf("%d \n", a);
   change_number(b);
   int result = sum_numbers_1(a, b);
   printf("result = %d \n", result);
   int result1 = calculate(a, b, '+'), result2 = calculate(a, b, '-'), result3 = calculate(a, b, '/');
   printf("result1 = %d \n", result1);
   printf("result2 = %d \n", result2);
   printf("result3 = %d \n", result3);
   printf("factorial = %d \n", factorial(5));
   print_n();
   //n++ - так делать нельзя, так как n локально определена внутри функции.
   print_static_variable();
   print_static_variable();
   print_static_variable();
   //надо скомпилировать несколько файлов сразу 
   //gcc zan6.c zan6_second.c -o zan6.exe; if ($?) { chcp 65001 > $null; ./zan6.exe }
   /*
   gcc - компилятор
   zan6.c, zan6.second.c - название файлов, которые надо скомпилировать
   -o - ключ компилятора, который говорит "сохрани результат (исполняемый файл под этим именем)"
   zan6.exe - название выходного файла
   ; - разделитель между командами
   if ($?) - выполняется только если компиляция прошла без ошибок
    {} - группировка команд в терминале
     chcp 65001 -смена кодировки консоли на UTF-8
     > $null - скрывает вывод команды chcp
     ./zan6.exe запускаем программу из текущейц папки
   */
   printf("%s \n", message1);
   print_zan6_second();
   return 0;
}

void print_message(char message[])
{
    printf("%s \n", message);
}

void hello1()
{
    printf("Hello1! \n");
}

void sum_numbers(int x, int y)
{
    printf("x + y = %d \n", x + y);
}

void increase_number(int x)
{
    x++;
    printf("x = %d \n", x);
}

void change_number(const int x)
{
    int x1 = x * 2;
    printf("x = %d \n", x);
    printf("x1 = %d \n", x1);
}

int sum_numbers_1(int x, int y)
{
    printf("x + y = %d \n", x + y);
    return x + y;
}

int calculate(int x, int y, char operation)
{
    if (operation == '+')
    {
        return x + y;
    }
    else if (operation == '-')
    {
        return x - y;
    }
    else
    {
        return 0;
    }
}

int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

void print_n()
{
    int n = 52;
    printf("n = %d \n", n);
    {
       int a = 20;
       int n = 54; //сокрытие переменных
       kk++;
       printf("kk = %d", kk);
    }
    //printf("a = %d \n", a);
}

void print_static_variable(){
    static int i = 0;
    i++;
    printf("i = %d \n", i);
}