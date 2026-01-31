#include <stdio.h>

struct company
{
    char* name;
    char* country;
};

struct phone
{
    char* title;
    int price;
    struct company manufacture;
};

struct person
{
    int age;
    char name[20];
};

/* struct person
{
    int age;
    char name[20];
} *p1, *p2 */

struct node
{
    char* value;
    struct node* next;
};

//Сначала надо объявить прототип color
struct color;

struct rectangle
{
    struct color* background;
    unsigned width;
    unsigned heigth;
};

struct color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct B;
struct A{
    struct B* b;
};

struct B{
    struct A* a;
};
//Если color будет стоять после rectangle, то будет ошибка


void print_person(struct person user)
{
    printf("name %s \n", user.name);
    printf("age %d \n", user.age);
}

void change_person(struct person* user)
{
    user->age = user->age + 1;
}

struct person1
{
    int age;
    char* name;
};

struct person1 create_person(char* name, int age)
{
    struct person1 user;
    user.name = name;
    user.age = age;
    return user;
}


typedef struct{
    int x;
    int y;
} point;

void print_point(point p){
    printf("(x: %d, y: %d) \n", p.x, p.y);
}


enum operation //арифметическая операция
{
    ADD,
    SUBSTRUCT,
    MULTIPLY
};

/* enum operation //арифметическая операция
{
    ADD = 5,
    SUBSTRUCT, //6
    MULTIPLY //7
    но также можно присваивать различные уникальные значения
}; */

struct BinaryOp
{
    int n1;
    int n2;
    enum { ADD11, SUBSTRUCT11, MULTIPLY11 } op;
};

enum operate //арифметическая операция
{
    ADD2 = 1,
    SUBSTRUCT2 = 2,
    MULTIPLY2 = 4
};

int calculate(int x, int y, enum operation op)
{
    switch (op)
    {
    case ADD2:
        return x + y;
    case SUBSTRUCT2:
        return x - y;
    case MULTIPLY2:
        return x * y;
    default:
        return 0;
    }
}

union ascii
{
    int digit;
    char symbol;
};

/*
char symbol
    1 байт  1 байт  1 байт  1 байт
                int digit

*/

typedef union
{
    int int_value;
    char* str_value;
} node_data;

typedef enum{
    NODE_STRING,
    NODE_INT
} node_type;

typedef struct{
    node_type type;
    node_data data;
} node1;

void print_node(node1 n){
    if (n.type == NODE_STRING)
    {
        printf("String: %s \n", n.data.str_value);
    }
    else if (n.type == NODE_INT)
    {
        printf("Number: %d \n", n.data.int_value);
    }
}

struct ppoint
{
    unsigned int x:5; //0 - 31 11111_2 = 31
    unsigned int y:3; //0 - 7
};

int main(void){
    struct phone iphone;/*  */
    iphone.title = "iphone 17 pro max";
    iphone.price = 110000;
    iphone.manufacture.name = "Apple";
    iphone.manufacture.country = "USA";

/*     printf("Input manufacture name of phone: \n");
    scanf("%s", iphone.manufacture.name); Можем записывать с клавиатуры в массив символов, например*/ 

    struct phone samsung = {"Samsung A21", 30000, {"Samsung", "republic of korea"}};
    printf("Phone: %s \n", iphone.title);
    printf("Price: %d \n", iphone.price);
    printf("Manufacture: %s \n", iphone.manufacture.name);
    printf("Phone: %s \n", samsung.title);
    printf("Price: %d \n", samsung.price);
    printf("Manufacture: %s \n", samsung.manufacture.name);

    //Указатели на структуры. Используя указатель на структуру, можно получить доступ к ее элементам. Есть два способа
    /*
    Применение операции разыменовывания
    (*указатель_на_структуру).имя_элемента

    указатель_на_структуру->имя_элемента
    */
    struct person andrew = {18, "Andrew"};
    struct person *p_andrew = &andrew;

    char* name = p_andrew->name;
    int age = (*p_andrew).age;

    printf("name = %s, age = %d \n", name, age);

    p_andrew->age = 32;
    printf("name = %s, age = %d \n", andrew.name, andrew.age);

    struct node andreww = {.value = "Andrew"};
    struct node gennady = {.value = "Gennady"};
    struct node alice = {.value = "Alice"};

    andreww.next = &gennady;
    gennady.next = &alice;

    struct node* pointer = &andreww;

    while(pointer != NULL)
    {
        printf("value = %s \n", pointer->value);
        pointer = pointer->next;
    }

    //struct person people[10]; массив из 10 структур person
    
    struct person people[] = { {23, "Tom"}, {24, "Alice"}, {25, "Bob"}, {26, "Donald"} };
    int n = sizeof(people) / sizeof(people[0]);
    for(int i = 0; i < n; i++)
    {
        printf("name: %s \t age: %d \n", people[i].name, people[i].age);
    }
    for (struct person *p = people; p < people + n; p++)
    {
        printf("name: %s \t age: %d \n", p->name, p->age);
    }

    //Структуры как параметр функции
    print_person(andrew);
    change_person(&andrew);
    print_person(andrew);
    struct person1 bobby = create_person("Bobby", 39);
    printf("name = %s, age = %d \n", bobby.name, bobby.age);


    //Размещение структур и их полей в памяти
    /*
    Поля структуры появляются в памяти в том же порядке, в котором они идут в объявлении структуры. Первое поле имеет тот же адрес, что и в 
    структура в целом. Каждое последующее поле располагает после предыдущего с учетом выраванивания. Выравнивание указывает, что поле 
    должно располагаться по адресу, которое кратно (делится без остатка ) выравниванию.
    */

    printf("sizeof(struct person1): %lu \n", sizeof(struct person1));
    printf("bobby address: %p \n", &bobby);
    printf("age address: %p \n", &bobby.age);
    printf("name address: %p \n", &bobby.name);

    //Составные литералы
    print_point((point){.x = 2, .y = 3});
    print_point((point){4, 5});

    /*
    Перечисление представляют типы данных, которые содержат набор констант, и каждой константе сопоставлено определенное значение. Перечисление определяется
    при помощи ключевого слова enum.

    enum название_перечисления {константа1, константа2, ...}
    */
    enum operation op;

    op = ADD;
    int opCode = MULTIPLY;
    printf("Operation: %d \n", op); //каждой константе присваивается свое значение. первой - 0, второй - 1.
    printf("Operation code: %d \n", opCode);

    struct BinaryOp mulop = { .n1 = 6, .n2 = 2, .op = MULTIPLY11 };
    printf("Operands: %d and %d. Operation: %d \n", mulop.n1, mulop.n2, mulop.op);

    enum operation op1 = MULTIPLY2;

    int result = calculate(5, 6, op1);
    printf("result: %d \n", result);

    result = calculate(5, 6, ADD2);
    printf("result: %d \n", result);

    result = calculate(5, 6, SUBSTRUCT2);
    printf("result: %d \n", result);

    /*
    Объединения (union). Все элементы объединения имеют нулевое смещение. В памяти накладываются друг на друга

    union имя_объединения
    {
    тип_элемента1;
    тип_элемента2
    ....
    }

    При определении переменной объединения мы ее можем сразу инициализировать, но только по первому элементу. В данном случае у ascii это digit, 
    поэтому передаю только целое число.
    */

    union ascii code = {110};
    printf("code: %d \n", code.digit);
    printf("symbol: %c \n", code.symbol);

    //Данные интепретируются по-разному.

    node1 n1;
    n1.type = NODE_INT;
    n1.data.int_value = 33;

    node1 n2;
    n2.type = NODE_STRING;
    n2.data.str_value = "Andrew";

    print_node(n1);
    print_node(n2);

    /*
    Битовые поля обеспечивают удобный доступ к отдельным битам данных. Формировать объекты с длиной, не кратной байту. экономия памяти.
    Битовое поле само по себе существовать не может. Оно может быть только жлементов структуры или объединение.

    struct имя_структуры
    {
    тип1 имя_поля1: ширина_поля1;
    тип2 имя_поля2: ширина_поля2;
    ...
    }
    В качестве типа поля можем использовать только int и различные его модификаторы
    */ 

    struct ppoint point1 = {0, 2};
    point1.x = 3;
    printf("x = %d, y = %d \n", point1.x, point1.y);
    return 0;
}
