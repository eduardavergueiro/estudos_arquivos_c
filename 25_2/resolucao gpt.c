#include <stdio.h>

typedef struct{
    int dia;
    int novos_casos;
    int obitos;
} Covid;

//questão 3
void medias(FILE *in, FILE *out, int k){

    Covid buf[k];
    Covid saida;

    int lidos = fread(buf, sizeof(Covid), k, in);

    while(lidos == k){

        int soma_casos = 0;
        int soma_obitos = 0;

        for(int i=0;i<k;i++){
            soma_casos += buf[i].novos_casos;
            soma_obitos += buf[i].obitos;
        }

        saida.dia = buf[k-1].dia;
        saida.novos_casos = soma_casos / k;
        saida.obitos = soma_obitos / k;

        fwrite(&saida, sizeof(Covid), 1, out);

        fseek(in, -(k-1)*sizeof(Covid), SEEK_CUR);
        lidos = fread(buf, sizeof(Covid), k, in);
    }
}

//questão 4
void combinar(FILE *a, FILE *b, FILE *out){

    Covid x, y;
    int temA = fread(&x,sizeof(Covid),1,a);
    int temB = fread(&y,sizeof(Covid),1,b);

    while(temA && temB){

        if(x.dia == y.dia){
            x.novos_casos += y.novos_casos;
            x.obitos += y.obitos;
            fwrite(&x,sizeof(Covid),1,out);

            temA = fread(&x,sizeof(Covid),1,a);
            temB = fread(&y,sizeof(Covid),1,b);
        }
        else if(x.dia < y.dia){
            fwrite(&x,sizeof(Covid),1,out);
            temA = fread(&x,sizeof(Covid),1,a);
        }
        else{
            fwrite(&y,sizeof(Covid),1,out);
            temB = fread(&y,sizeof(Covid),1,b);
        }
    }

    while(temA){
        fwrite(&x,sizeof(Covid),1,out);
        temA = fread(&x,sizeof(Covid),1,a);
    }

    while(temB){
        fwrite(&y,sizeof(Covid),1,out);
        temB = fread(&y,sizeof(Covid),1,b);
    }
}