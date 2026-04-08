#include <stdio.h>

typedef struct{
    int mat;
}Aluno;

int existe_arq2(int proc, FILE *bPtr, int qtd){

    int inicio = 0;
    int fim = qtd -1;
    Aluno b;

    while(inicio <= fim){
        int meio = (inicio + fim)/2;

        fseek(bPtr, meio * sizeof(Aluno), SEEK_SET);
        fread(&b, sizeof(Aluno), 1, bPtr);

        if(b.mat == proc){
            return 1; 
        }
        if(b.mat < proc){
            inicio = meio + 1;
        }else{
            fim = meio - 1;
        }
        
    }

    return 0;
}


//acho que tem q tirar o que ta no arq1 que tambem está no 2
int main(){

    FILE *aPtr, *bPtr, *rPtr;
    Aluno a;
    aPtr = fopen("arquivoA.dat", "rb"); //nao esquecer do b quando binário
    bPtr = fopen("arquivoB.dat", "rb");
    rPtr = fopen("resultado.dat", "wb");

    //parte da busca binaria
    int qtdB;
    long posB;
    fseek(bPtr, 0, SEEK_END);
    posB = ftell(bPtr);
    qtdB = posB/sizeof(Aluno);

    while(fread(&a, sizeof(Aluno), 1, aPtr) == 1){
        if(existe_arq2(a.mat, bPtr, qtdB) == 0){
            fwrite(&a, sizeof(Aluno), 1, rPtr);
        }
    }

    fclose(aPtr);
    fclose(bPtr);
    fclose(rPtr);

    return 0;
}