// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#ifndef __ESTRUTURAS__
#define __ESTRUTURAS__

#define PI 3.141592654 //define número de Pi para cálculo da rotação

//estrutura das imagens
typedef struct{
		char codigo[5];
		char comentario[40];
		int colunas; 
		int linhas;
		int max;
		int **matriz;
	}Estrutura;

#endif