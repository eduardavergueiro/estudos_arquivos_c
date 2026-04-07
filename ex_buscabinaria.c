#include <stdio.h>

int main() {
    int a[] = {10, 20, 30, 40, 50, 60, 70};
    int b = 60;

    int contador = 0;
    int inicio = 0;
    int fim = sizeof(a)/sizeof(a[0]) - 1;

    while (inicio <= fim){
        contador++;

        int meio = (inicio + fim) / 2;

        if (a[meio] == b){
            printf("Achei %d na posicao %d\n", b, meio);
            break;
        }
        else if (b > a[meio]){
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }
    printf("Contador: %d\n", contador);

    return 0;
}