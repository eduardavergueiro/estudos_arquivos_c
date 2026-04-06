#include <stdio.h>

typedef struct {
    char cpf[12];
    char nome[80];
    int mes;
    int ano;
    float valor;
} Pagamento;

float total_pago_mes_ano(int mes, int ano){
        
    FILE *brPtr;
    float total_pago = 0;
    Pagamento p;

    brPtr = fopen("beneficios.dat", "rb");

    //sempre lembrar que não adianta nada abrir o arquivo e ter a variável se não colocar o conteúdo na variável com fread
    while(fread(&p, sizeof(Pagamento), 1, brPtr) == 1){
        if(p.mes == mes && p.ano == ano){
            total_pago += p.valor;
        }
        if(p.mes > mes && p.ano >= ano){
            break;
        }
    }

    fclose(brPtr);

    return total_pago;
}

int main(){

    int mes, ano;
    mes = 1;
    ano = 2020;
    total_pago_mes_ano(mes, ano);

    return 0;
}