#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*extern int values[];
extern char names[][10];
*/
extern int add(int, int);
extern int sub(int, int);
extern int get_ops_count();

extern char *messages[];

void smart_calc(int a, int b, int op){
    static int call_count = 0;
    call_count++;

    //1. Случайно сообщение
    int msg_idx = rand() % 4;
    printf("%s \n", messages[msg_idx]);

    int result;
    char op_char;
    if (op == 0){
        result = add(a, b);
        op_char = '+';
    } else {
        result = sub(a, b);
        op_char = '-';
    }

    printf("Операция %d: %d %c %d = %d, всего операций: %d\n", call_count, a, op_char, b, result, get_ops_count());
}
/*
void print_info(int i){
    printf("Name: %s, Value: %d \n", names[i], values[i]);
}*/

int main(void){
    /*
    int size = 3;
    for (int i = 0; i < size; i++){
        print_info(i);
    }*/
    
    //запуск gcc main.c tools.c texts.c -o main.exe; if ($?) { chcp 65001 > $null; ./main.exe }. либо просто gcc main.c tools.c texts.c -o main.exe (вдруг сработает)
    srand(time(NULL));
    smart_calc(15, 7, 0);
    smart_calc(20, 8, 1);
    smart_calc(5, 3, 0);
    return 0;
}