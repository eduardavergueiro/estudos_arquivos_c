#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE *f;
    char c;
    int cont = 0;

    if (argc < 2) {
        printf("Passe o arquivo como parametro\n");
        return 1;
    }

    f = fopen(argv[1], "r");

    if (f == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    while ((c = fgetc(f)) != EOF) {
        if (c == '{')
            cont++;
        else if (c == '}') {
            cont--;
            if (cont < 0) {
                printf("Nao balanceado\n");
                fclose(f);
                return 0;
            }
        }
    }

    if (cont == 0)
        printf("Balanceado\n");
    else
        printf("Nao balanceado\n");

    fclose(f);
    return 0;
}