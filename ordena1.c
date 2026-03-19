#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

//são 699307 linhas, ent 349654 pra cada um (uma linha a mais)

int main(int argc, char**argv)
{
	FILE *f, *saidaA, *saidaB;
	Endereco *e;
	long posicao, qtd, metade;

	f = fopen("cep.dat","rb"); //abre o arquivo; fopen("arquivo", "modo: rb -> leitura binária wb -> escrita binaria")
	fseek(f,0,SEEK_END); //vai ate o final do arquivo; fseek("arquivo", offset em bytes, SEEK_:SET(inciio), END, CUR(current))
	posicao = ftell(f); //retorna posicao atual em bytes; ftell("arquivo")
	qtd = posicao/sizeof(Endereco); //calcula quantos tem pq a posicao tem o numero total de bytes (ja q tava no final) e o sizeof(Endereco) tem o tamanho de cada endereço
	e = (Endereco*) malloc(qtd*sizeof(Endereco)); //aloca a memoria (qtd de linhas * tamanho de cada linha) -- acho q o e é um array de struct Endereco
	rewind(f); //volta pro inicio do arquivo; rewind("arquivo")
	if(fread(e,sizeof(Endereco),qtd,f) == qtd) //le os dados do arquivo para a memoria (alocada em e); fread(destino, tamanho, quantidade, arquivo)
	{
		printf("Lido = OK\n");
	}
	qsort(e,qtd/2,sizeof(Endereco),compara); //ordena a primeira parte (a partir da posicao e) do vetor até a metade (qtd/2)
	printf("Primeira parte ordenada! :D\n");
	saidaA = fopen("cep-ordenado-A.dat","wb"); //cria arquivo para escrita (wb) e guarda na variável saida
	fwrite(e,sizeof(Endereco),qtd/2,saidaA); //escreve dados da memoria pro arquivo novo; fwrite(origem, tamanho, quantidade, arquivo)
	fclose(saidaA); //fecha o arquivo A

	//inicio da ordenação do B
	qsort(e + qtd/2, qtd - qtd/2, sizeof(Endereco), compara);
	printf("Segunda parte ordenada :)\n");
	saidaB = fopen("cep-ordenado-B.dat", "wb");
	fwrite(e + qtd/2, sizeof(Endereco), qtd - qtd/2, saidaB); //n entendi mto bem o primeiro parâmetro, origem é o ponto de partida ou tipo, a base de dados?
	fclose(saidaB);

	free(e);
	return 0;
}