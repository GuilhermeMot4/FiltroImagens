// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "estruturas.h"
#include "trataImagem.h"
#include "acessaImagem.h"
#include "trataLinhasComando.h"

//faz cálculo do filtro LBP
int calcLBP(int *v){
	int i,soma;

	soma = 0;
	for (i = 0; i < 8; i++){
		soma += (v[i] * pow(2,i));	
	}	
	return soma;
}

//implementação do filtro negativo
void negativo(Estrutura *Imagem){
	int i,j;
	//formatação
	for(i= 0;i < Imagem->linhas;i++){
		for(j= 0;j < Imagem->colunas;j++){
			Imagem->matriz[i][j] = Imagem->max - Imagem->matriz[i][j]; //inversão
		}
	}
}
//implementação do filtro lbp
Estrutura * lbp(Estrutura *Imagem){
	int i,j,a,b,cont, valores[8];

	//alocação de memória para a estrutura
	Estrutura *ImagemFormatada;
	ImagemFormatada = (Estrutura *) malloc(sizeof(Estrutura));

	//cópia dos dados
	strcpy(ImagemFormatada->codigo,Imagem->codigo);
	ImagemFormatada->colunas = Imagem->colunas;
	ImagemFormatada->linhas = Imagem->linhas;
	ImagemFormatada->max = Imagem->max;
	//alocação de memória para a imagem
	ImagemFormatada->matriz = alocaImagem(ImagemFormatada->linhas,ImagemFormatada->colunas); //aloca espaço para a imagem formatada

	for(i= 0;i < Imagem->linhas;i++){ //inicializa a imagem formatada com os valores da imagem inicial
		for(j= 0;j < Imagem->colunas;j++){
			ImagemFormatada->matriz[i][j] = Imagem->matriz[i][j];
		}
	}

	//formatação
		for(i= 1;i < Imagem->linhas-1;i++){
			for(j= 1;j < Imagem->colunas-1;j++){ //laço que varre a imagem sem considerar as bordas
				cont = 0;
				for(a = i-1;a <= i+1;a++){
					for(b = j-1;b <= j+1;b++){ //laço que trata cada região 3x3
						if(a != i || b != j){
							if(ImagemFormatada->matriz[a][b] >= ImagemFormatada->matriz[i][j]) //se valor da posição atual for maior ou igual que a do meio
								valores[cont] = 1;
							else //se for menor
								valores[cont] = 0;
							cont++;			
						}
					}
				}
				ImagemFormatada->matriz[i][j] = calcLBP(valores); //chama função que calcula filtro para cada região 3x3
			}
		}
		return ImagemFormatada;
	}
//implementação do filtro rotação
Estrutura * rotacao(Estrutura *Imagem){

	int i,j,x,y;
	int desl_x, desl_y;
	int vertice[4][2];
	extern double angulo;
	double radianos;
	double se, co;

	//alocação de memória para a estrutura
	Estrutura *ImagemFormatada;
	ImagemFormatada = (Estrutura *) malloc(sizeof(Estrutura));

	//cópia dos dados
	strcpy(ImagemFormatada->codigo,Imagem->codigo);
	ImagemFormatada->max = Imagem->max;


	radianos = (angulo*PI/180); //converte graus para radianos

	//cálculo do seno e cosseno do ângulo
	se = sin(radianos);
	co = cos(radianos);

	//rotaciona os 4 vertices da matriz e armazena em um vetor[4][2]
	x = 0;
	y = 0;

	vertice[0][0] = round(x * co + y * se);
	vertice[0][1] = round(y * co - x * se);


	x = Imagem->linhas - 1;
	y = 0;

	vertice[1][0] = round(x * co + y * se);
	vertice[1][1] = round(y * co - x * se);


	x = 0;
	y = Imagem->colunas - 1 ;

	vertice[2][0] = round(x * co + y * se);
	vertice[2][1] = round(y * co - x * se);


	x = Imagem->linhas - 1;
	y = Imagem->colunas - 1;

	vertice[3][0] = round(x * co + y * se);
	vertice[3][1] = round(y * co - x * se);

	//calcula o deslocamento e o tamanho da nova da imagem formatada
	if (angulo >= 0 && angulo <=90){
		ImagemFormatada->linhas  = abs(vertice[0][0]) + abs(vertice[3][0]) + 1;
		ImagemFormatada->colunas = abs(vertice[1][1]) + abs(vertice[2][1]) + 1;

		desl_x = 0;
		desl_y = abs(vertice[1][1]);
	}
	else if (angulo > 90 && angulo <=180){
		ImagemFormatada->linhas  = abs(vertice[1][0]) + abs(vertice[2][0]) + 1;
		ImagemFormatada->colunas = abs(vertice[0][1]) + abs(vertice[3][1]) + 1;

		desl_x = abs(vertice[1][0]);
		desl_y = abs(vertice[3][1]);
	}
	else if (angulo > 180 && angulo <=270){
		ImagemFormatada->linhas  = abs(vertice[0][0]) + abs(vertice[3][0]) + 1;
		ImagemFormatada->colunas = abs(vertice[1][1]) + abs(vertice[2][1]) + 1;

		desl_x = abs(vertice[3][0]);
		desl_y = abs(vertice[2][1]);
	}
	else if (angulo > 270 && angulo <=360){
		ImagemFormatada->linhas  = abs(vertice[1][0]) + abs(vertice[2][0]) + 1;
		ImagemFormatada->colunas = abs(vertice[0][1]) + abs(vertice[3][1]) + 1;

		desl_x = abs(vertice[2][0]);
		desl_y = 0;
	}

	//aloca memória para a imagem formatada
	ImagemFormatada->matriz = alocaImagem(ImagemFormatada->linhas, ImagemFormatada->colunas);

	//preenche com branco nos pixels
	for (i=0; i < ImagemFormatada->linhas; i++)
		for (j=0; j < ImagemFormatada->colunas; j++)
			ImagemFormatada->matriz[i][j] = Imagem->max;


	//aplica o filtro de rotação
	for(i=0; i < Imagem->linhas; i++)
		for(j=0; j < Imagem->colunas; j++)
		{
			int xr = round(i * co + j * se);
			int yr = round(j * co - i * se);

			xr += desl_x;
			yr += desl_y;

			ImagemFormatada->matriz[xr][yr] = Imagem->matriz[i][j];
		}

	return ImagemFormatada;
}
