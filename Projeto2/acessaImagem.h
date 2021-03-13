// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#ifndef __ACESSA_IMG__
#define __ACESSA_IMG__

#include "estruturas.h"

	//estrutura das funções de acesso a imagem pgm
	int ** alocaImagem(int linhas, int colunas);

	void desalocaImagem(int **matriz);
	
	Estrutura * leImg(char *entrada);
	
	void escreveImg(Estrutura *Imagem, char *saida);
	
#endif