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
	Estrutura *imgFormatada;
	extern char *entrada;
	extern char *saida;

	rotacaoLC(argc, argv);
	img = leImg(entrada);
	imgFormatada = rotacao(img);
	escreveImg(imgFormatada, saida);
	desalocaImagem(img->matriz);
	desalocaImagem(imgFormatada->matriz);
	free(img);
	free(imgFormatada);
	
	return (0);
}