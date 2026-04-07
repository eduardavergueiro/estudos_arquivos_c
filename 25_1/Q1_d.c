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
    Pagamento p, maior, menor;
    int ano_atual;

    //ESQUECI DE ABRIR O ARQUIVO
    bPtr = fopen("beneficios.dat", "rb");

    fread(&p, sizeof(Pagamento), 1, bPtr); //faltou testar o arquivo
    maior = menor = p;
    ano_atual = p.ano;

    while (fread(&p, sizeof(Pagamento), 1, bPtr) == 1)
    {
        if(p.ano != ano_atual){
            printf("Maior: %s%s%d%d%f\n", maior.cpf, maior.nome, maior.mes, maior.ano, maior.valor);
            printf("Menor: %s%s%d%d%f\n", menor.cpf, menor.nome, menor.mes, menor.ano, menor.valor);
        
            ano_atual = p.ano;
            maior = menor = p;
        }

        if(p.valor > maior.valor){
            maior = p;
        }
        if(p.valor < menor.valor){
            menor = p;
        }
    }

    //pro ultimo ano do arquivo
    printf("Maior: %s%s%d%d%f\n", maior.cpf, maior.nome, maior.mes, maior.ano, maior.valor);
    printf("Menor: %s%s%d%d%f\n", menor.cpf, menor.nome, menor.mes, menor.ano, menor.valor);

    fclose(bPtr);

    return 0;
}