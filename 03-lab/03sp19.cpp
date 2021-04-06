#include <iostream>
#include <ctime>
#include <cstdlib>

void fill(int array[], size_t size);
void fill(int array[], int array1[], int array2[], size_t size);
void print_array(const int a[], size_t size);

int main()
{
    std::srand(std::time(nullptr));

    const size_t size = rand() % 5 + 1;

    int* array1 = new int[size];
    int* array2 = new int[size];
    int* array = new int[2*size];


    fill(array1, size);
    fill(array2, size);
    fill(array, array1, array2, size);

    print_array(array1, size);
    print_array(array2, size);
    print_array(array, 2*size);

    delete [] array1;
    delete [] array2;
    delete [] array;

    return 0;
}

void fill(int a[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        a[i] = std::rand() % 100 + 1;
    }
}

void fill(int array[], int array1[], int array2[], size_t size)
{
    asm
    (
        "push %[array]\n\t"                 

        "movl %[size], %%ecx\n\t" 
        "movl %[array1], %%ebx\n\t" 
        "movl %[array], %%edx\n\t"

        "loop1:\n\t"
            "movl (%%ebx), %%eax\n\t" 
            "push %%ecx\n\t"
            "movl (%%edx), %%ecx\n\t" 
            "movl %%eax, %%ecx\n\t"
            "movl %%ecx, (%[array])\n\t" 
            "popl %%ecx\n\t"

            "addl $4, %%ebx\n\t" 
            "addl $8, %%edx\n\t" 
            "decl %%ecx\n\t" 
            "cmpl $0, %%ecx\n\t"
            "jne loop1\n\t"

        "movl %[array2], %%ebx\n\t"
        "pop %%edx\n\t"
        "addl $4, %%edx\n\t"
        "movl %[size], %%ecx\n\t"

        "jmp loop2\n\t"

        "loop2:\n\t"
            "movl (%%ebx), %%eax\n\t" 
            "push %%ecx\n\t"
            "movl (%%edx), %%ecx\n\t" 
            "movl %%eax, %%ecx\n\t"
            "movl %%ecx, (%[array])\n\t" 
            "popl %%ecx\n\t"

            "addl $4, %%ebx\n\t" 
            "addl $8, %%edx\n\t" 
            "decl %%ecx\n\t" 
            "cmpl $0, %%ecx\n\t"
            "jne loop2\n\t"
        :
        :[size]"m"(size),
        [array1]"m"(array1), [array2]"m"(array2), [array]"d"(array)
        :"%ecx", "%ebx"
    );
}

void print_array(const int a[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << a[i] << ' ';
    }

    std::cout << '\n';
}
