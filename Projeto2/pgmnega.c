// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "estruturas.h"
#include "acessaImagem.h"
#include "trataImagem.h"
#include "trataLinhasComando.h"

int main(int argc, char **argv){

	Estrutura *img;
	img = (Estrutura *) malloc(sizeof(Estrutura));
	extern char *entrada;
	extern char *saida;

	negativoLC(argc, argv);
	img = leImg(entrada);
	negativo(img);
	escreveImg(img, saida);
	desalocaImagem(img->matriz);
	free(img);

	return (0);
}