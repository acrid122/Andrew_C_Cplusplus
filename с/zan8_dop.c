#include <stdio.h>
int main(int argc, char *argv[]){ 
    //argc - представляет количество аргументов командной строки, который переданы приложению
    //argv - представляет указатель на массив строк, который представляет переданный набор аргументов
    for (int i = 0; i < argc; i++){
        printf("%s \n", argv[i]);
    }
    return 0;
}

//сначала компиляция gcc zan8_dop.c -o zan8_dop
//запуск - ./zan8_dop 1 hello
//argv[0] = "./zan8_dop"
