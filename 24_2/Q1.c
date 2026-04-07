#include <stdio.h>

typedef struct 
{
    int id;
    char nome[30];
    char especie[30];
    int idade;
    float peso;
}Animal;

//questao A
void busca_registro(FILE *aPtr){

    int proc, qtd;
    long pos;
    Animal a;

    printf("ID do animal: ");
    scanf("%d", &proc);

    fseek(aPtr, 0, SEEK_END); //0 pq só quer posicionar no fim
    pos = ftell(aPtr);
    qtd = pos/sizeof(Animal);

    int inicio = 0;
    int fim = qtd -1; //-1 pra n acessar fora do arquivo ja q os indices começam em 0

    while(inicio <= fim){
        int meio = (inicio + fim)/2;

        fseek(aPtr, meio * sizeof(Animal), SEEK_SET);
        fread(&a, sizeof(Animal), 1, aPtr);

        if(a.id == proc){
            printf("%s%s%d%f%d", a.nome, a.especie, a.idade, a.peso, a.id);
            //fclose(aPtr); sem fclose pq o arquivo n abriu aqui
            return; //não break pq é pra sair da função toda
        }
        if(a.id < proc){
            inicio = meio + 1;
        }else{
            fim = meio - 1;
        }
        
    }
    printf("id nao encontrado");
}

//questao B
void incluir(FILE *aPtr){

    Animal a, b;
    printf("dados do animal: ");
    //sepre ler na ordem da struct
    scanf("%d %s %s %d %f", &a.id, a.nome, a.especie, &a.idade, &a.peso); //n esquecer & qnd n é string

    rewind(aPtr); //porque o arquivo pode estar fora do inicio quando a função for chamada

    while(fread(&b, sizeof(Animal), 1, aPtr) == 1){
        if(b.id == a.id){
            printf("esse ID já foi registrado.");
            return;
        }
    }
    fseek(aPtr, 0, SEEK_END); //vai pro final pra escrever no final
    fwrite(&a, sizeof(Animal), 1, aPtr);
}

//questão C
void alterar_registro(FILE *aPtr){

    Animal a, b;
    int proc;

    printf("insira o ID: ");
    scanf("%d", &proc);
    printf("novos dados: ");
    scanf("%d %s %s %d %f", &a.id, a.nome, a.especie, &a.idade, &a.peso);

    while(fread(&b, sizeof(Animal), 1, aPtr) == 1){
        if(b.id == proc){
            printf("dados antigos: %d %s %s %d %f", b.id, b.nome, b.especie, b.idade, b.peso);
            
            fseek(aPtr, -sizeof(Animal), SEEK_CUR); //precisa voltar um depois de ler, se não escreve no proximo
            fwrite(&a, sizeof(Animal), 1, aPtr);
            return;
        }
    }
    printf("ID não encontrado :(");
}


int main(){

    FILE *aPtr;

    aPtr = fopen("animais.dat", "rb+");

    busca_registro(aPtr);
    incluir(aPtr);

    fclose(aPtr);

    return 0;
}