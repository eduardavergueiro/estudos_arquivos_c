#include <stdio.h>

typedef struct 
{
    int id;
    char nome[30];
    char especie[30];
    int idade;
    float peso;
}Animal;



int main(){

    FILE *aPtr;

    aPtr = fopen("animais.dat", "rw");

    

    return 0;
}