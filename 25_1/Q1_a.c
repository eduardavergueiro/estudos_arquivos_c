#include <stdio.h>

typedef struct {
    char cpf[12];
    char nome[80];
    int mes;
    int ano;
    float valor;
} Pagamento;

int main(){

    FILE *bPtr;
    int qtd;
    long pos; //ftell retorna long
    
    if(bPtr = fopen("beneficios.dat", "rb") == NULL){
        printf("Erro ao abrir o arquivo");
    }
    else{
        fseek(bPtr, 0, SEEK_END);
        pos = ftell(bPtr);
        qtd = pos/sizeof(Pagamento);
        printf("Total em bytes: %d\n", pos);
        printf("Total de registros: %d\n", qtd);
    }

    return 0;
}