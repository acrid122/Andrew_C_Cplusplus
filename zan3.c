#include <stdio.h>
#include <locale.h>
int main(void){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int x = 2 + 5;
    float y = 2 + 5;

    int a, b, c;
    a = b = c = 90 + 7;

    /*
    a += b -> a = a + b
    a -= b -> a = a - b
    a *= b -> a = a * b
    a /= b -> a = a / b
    a %= b -> a = a % b
    a <<= b -> a = a << b
    a >>= b -> a = a >> b
    a &= b -> a = a & b
    a |= b -> a = a | b
    a ^= b -> a = a ^ b
    */

    char c1 = 6;
    int d = c1; //от типа char к типу int
    /*
    Если 1 из операндов имеет тип long double, то второй операнд тоже будет преобразован в тип long double. Если предыдущий пункт не выполняется,
    то второй операнд будет преобразован к типу dobule, если один из операндо double...
    */
    int number1 = 10;
    double number2 = 4;
    double result = number1 + number2;
    printf("result = %f \n", result);

    int a2 = 10;
    int b2 = 4;
    int c2 = a2 / b2; //2 оба операнда представляют целые числа
    double d2 = a2 / b2; //2.000000, получаем целый ответ, так как оба операнда целые
    double e2 = (double)a2 / (double)b2; //2.5000
    printf("c = %d \n", c2);  
    printf("c = %f \n", d2); 
    printf("c = %f \n", e2);
    int number3 = 80;
    char symbol = (char) number3; //chr(90), ord('P')
    printf("symbol = %c \n", symbol);
    printf("symbol (int code) %d \n", symbol);
    //В ряде случаев преобразования сопровождаются потерей информации, например, когда числа большей разрядности преобразуем в число меньшей разрядности.
    //Без потери информации работают следующие преобразования
    /*
    char -> short -> int -> long
    unsigned char -> unsigned short -> unsigned int -> unsigned long
    float -> double -> long double
    */

    int number4 = 300;
    char code = number4; //потеря точности - число number1 усекается до 1 байта
    //0000000100101100 -> 300; 00101100 -> 44
    printf("code %d \n", code);

    short number5 = 100000;
    printf("number5 %d \n", number5); //усекается до разрядности типа short - два байта

    int a3 = 10;

    // if (условие) инструкция;

    if (a3 == 10) printf("Hello 10 \n");

    if (0) printf("C is better than Python");

    if (a3 == 10){
        printf("if statement \n");
        printf("hello 10 \n");
    }

    int a4 = 50;
    int b4 = 50;

    if (a4 > 10 && b4 < 100){
        printf("оба условия верны \n");
    }

    //Для одной инструкции в if/else

    if (a4 > 10)
        printf("a4 больше 10 \n");
    else
        printf("a4 меньше 10 \n");

    if (a4 > 10)
    {
        printf("a4 больше 10 \n");
        printf("урааа \n");
    }
    else
    {
        printf("a4 меньше 10 \n");
        printf("не урааа \n");
    }

    //else if

    if (a4 > 10)
    {
        printf("a4 больше 10 \n");
        printf("урааа \n");
    }
    else if (a4 == 10)
    {
        printf("a4 равно 10 \n");
        printf("урааа \n");
    }
    else
    {
        printf("a4 меньше 10 \n");
        printf("не урааа \n");
    }

    /*switch case
    switch case - соответствие шаблону. в скобках при switch идет сравниваемое значение. значение этого выражения последовательно
    сравниваются со значениями после операторов case (случаи). если совпадение будет найдено, то будет выполняться блок код внутри данного case
    */
    int a5 = 20;

    switch (a5)
    {
        case 10:
            printf("a5 равно 10 \n");
            break; //при его выполнении происходит выход из инструкции
        case 20:
            printf("a5 равно 20 \n");
            break;
    }

    a5 = 10; //без break. Будут выполняться все последующие блоки case, пока не встретится break или конец конструкции switch
    switch (a5)
    {
        case 10:
            printf("a5 равно 10 \n");
        case 20:
            printf("a5 равно 20 \n");
    }
    //default

    a5 = 30; //dafult - случай по умолчанию. он не является обязательным
    switch (a5)
    {
        case 10:
            printf("a5 равно 10 \n");
            break;
        case 20:
            printf("a5 равно 20 \n");
            break;
        default:
            printf("a5 не равно 10 и 20 \n");
            break;
    }

    //Тернарный оператор - условие в одну строку. сокращение простейших условий
    
    int a6 = 7, b6 = 8;

    int z = a6 > b6 ? a6 + b6 : a6 - b6;

    //условие ? значение, если условие истинно : значение, если условие ложно

    //Циклы

    /*
    Цикл for
    for (инициализация; условие; приращение)
    {
     тело цикла
    }
    Каждый проход цикла/шаг называется итерацией.
    */
    for (int a = 0; a < 6; a++){
        printf("%d \n", a);
    }
    int a7 = 1;
    for ( ; a7 < 10 ; )
    {
        printf("%d * %d = %d \n", a7, a7, a7 * a7);
        a7++;
    }
    for ( ; a7 < 10; a7++)
    {
        printf("%d * %d = %d \n", a7, a7, a7 * a7);
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            printf("%d \t", i * j);
        }
        printf("\n");
    }

    /*
    В цикле do...while сначала выполняется код цикла, а потом происходит проверка условия в while. Код точно выполнится хотя бы 1 раз
    */
   int a8 = 6;

   do
   {
     printf("%d", a8);
     a8--;
   } while (a8 > 0);
   
   /*
   while сразу проверяет истинность некоторого условия, и если условие истинно, то код цикла выполняется
   */
   a8 = 6;
   while (a8 > 0)
   {
        printf("%d \n", a8);
        a8--;
   }

   //операторы break/continue
   //break - досрочный выход из цикла
    a7 = 1;
    for ( ; ; )
    {
        printf("%d * %d = %d \n", a7, a7, a7 * a7);
        a7++;
        if (a7 > 10) break;
    }
    //continue производит переход к следующей итерации (младший брат break). пропускает блок кода, находящийся под ним в рамках цикла
    int result1 = 0;
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0) continue;
        result1 += i;
    }
    printf("result = %d \n", result1);

    //Введение в массивы и строки
    /*
    Массив - набор однотипных значений. Индексы указываются в квадратных скобках (при обращении к элементу) после названия массива и начинаются с нуля.

    тип_переменной название массива [длина массива]
    */
    int numbers[4];
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;
    printf("numbers[0] = %d \n", numbers[0]);

    //Инициализатор
    int numbers1[4] = {1, 2, 3, 4}; //инициализация массивов

    //При инициализации массива можно явно не указывать его длину. В этом случае длина массива будет вычисляться исходя из количества элементов в
    //инициализаторе
    int numbers2[] = {1, 2, 3};

    //Необязательно инициализировать массив значениями для всех его элементов

    int numbers3[10] = {1}; //есть значение только для 1 элемента, а остальные элементы получат значение по умолчанию - 0

    int numbers4[5] = {[0] = 2, [3] = 6}; //элемент с индексом 0 будет 2, а с индексом 3 будет 6. остальные будут 0 (как значение по умолчанию)

    //Размер и количество элемнтов массива
    //оператор sizeof - возвращает размер массива в байтах и результат будет иметь тип данных size_t. size_t фактически является псевдонимом unsigned long long, то есть 64-разрадное положительное число
    printf("%f \n", (double) 4000000 / (double) (1024 * 1024) ); //3 Мбайт
    //int numbers1[4] = {1, 2, 3, 4};
    size_t size = sizeof(numbers1);
    size_t count = size / sizeof(int);
    printf("numbers1 size: %zu \n", size);
    printf("numbers1 count %zu \n", count);

    //Динамическое вычисление значений массива.

    int sizes[] = {sizeof(int), sizeof(long), sizeof(long long)};
    printf("%d \n", sizes[0]);

    //Перебор элементов массива
    int numbers5[] = {10, 20, 30, 40, 50, 60};
    int count5 = sizeof(numbers5) / sizeof(numbers5[0]);
    for (int i = 0; i < count5; i++)
    {
        printf("numbers5[%d] = %d \n", i, numbers5[i]);
    }
    int numbers5[] = {10, 20, 30, 40, 50, 60};
    size_t count5 = sizeof(numbers5) / sizeof(numbers5[0]);
    for (size_t i = 0; i < count5; i++) //лучше так, потому что может не вписаться в диапазон
    {
        printf("numbers5[%d] = %d \n", i, numbers5[i]);
    }
   return 0;

}


