#include <stdio.h>
#include <stddef.h>

void print_int(const void* p)
{
    printf("%d ", *(const int *)p);
}

void print_double(const void* p)
{
    printf("%.2f ", *(const double *)p);
}

void print_array(void* arr, size_t n, size_t elem_size, void(*printer)(const void*))
{
    const char* bytes = (const char *) arr;
    for (size_t i = 0; i < n; i++)
    {
        printer(bytes + i * elem_size);
    }
}

#define PRINT_ARRAY_INT(arr) print_array(arr, sizeof(arr)/sizeof((arr)[0]), sizeof(int), print_int)
#define PRINT_ARRAY_DOUBLE(arr) print_array(arr, sizeof(arr)/sizeof((arr)[0]), sizeof(double), print_double)

int main(void){
    int numbers[] = {10, 20, 30};
    double values[] = {3.1415, 2.718};
    printf("int numbers: \n");
    PRINT_ARRAY_INT(numbers);
    printf("double numbers: \n");
    PRINT_ARRAY_DOUBLE(values);
    return 0;
}