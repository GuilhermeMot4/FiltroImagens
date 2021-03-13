// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acessaImagem.h"

	//aloca memória para a imagem
	int ** alocaImagem(int linhas, int colunas)
	{
		int** matriz;
		int i;

		matriz = malloc (linhas * sizeof(int *));

		matriz[0] = malloc(linhas * colunas * sizeof(int));

		for (i=1; i<linhas; i++)
			matriz[i] = matriz[0] + i * colunas;

		return matriz;
	}

	//libera memória ocupada pela imagem
	void desalocaImagem(int **matriz)
	{
		free(matriz[0]);
		free(matriz);
	}

	//leitura de imagem pgm P2 ou P5
	Estrutura * leImg(char *entrada){
		int i,j;
		Estrutura *Imagem;
		Imagem = (Estrutura *) malloc(sizeof(Estrutura));
		FILE *arq ;
		
		//abre arquivo de imagem no modo leitura
		if (entrada)
		{
  			arq = fopen(entrada, "r");
  			if (!arq)
				perror("Não foi possível abrir o arquivo de entrada!");
		}
		else{ //senão recebe da entrada padrão
			arq = stdin;	
		}

		//leitura das informações
		fgets(Imagem->codigo, 5, arq);
		do{
			fgets(Imagem->comentario,80,arq);
		}while(strchr(Imagem->comentario, '#')); //ignora a linha de comentário, caso exista
		sscanf(Imagem->comentario,"%d %d", &Imagem->colunas, &Imagem->linhas);
		fscanf(arq, "%d", &Imagem->max);
		Imagem->matriz = alocaImagem(Imagem->linhas,Imagem->colunas);
		if(strcmp("P2\n", Imagem->codigo) == 0){ //leitura dos bits da imagem para formato P2
			for(i= 0;i < Imagem->linhas;i++){
				for(j= 0;j < Imagem->colunas;j++){
					fscanf(arq, "%d", &Imagem->matriz[i][j]);
				}
			}
		}else{ //para formato P5
			for(i= 0;i < Imagem->linhas;i++){
				for(j= 0;j < Imagem->colunas;j++){
					fread(&Imagem->matriz[i][j],sizeof(int),1,arq);
				}
			}
		}	
		
		//fecha o arquivo de leitura e retorna a Imagem lida
		fclose (arq) ;
		return Imagem;
	}
	
	//escreve a imagem formatada em outra arquivo pgm
	void escreveImg(Estrutura *Imagem, char *saida){
		int i,j;
		FILE *arq ;

		//abre arquivo de saída no modo escrita
		if (saida)
		{
  			arq = fopen(saida, "w");
  			if (!arq)
				perror("Não foi possível abrir o arquivo de saída!");
		}
		else{ //senão, recebe a saída padrão
			arq = stdout;	
		}
		fputs(Imagem->codigo, arq);
		fprintf(arq, "%d %d\n", Imagem->colunas, Imagem->linhas);
		fprintf(arq, "%d\n", Imagem->max);
		if(strcmp("P2\n", Imagem->codigo) == 0){ // escrita para formato P2
			for(i= 0;i < Imagem->linhas;i++){
				for(j= 0;j < Imagem->colunas;j++){
					fprintf(arq, "%3d ", Imagem->matriz[i][j]);
				}
				fprintf(arq, "\n");
			}			
		}else{ //escrita no formato P5
			for(i= 0;i < Imagem->linhas;i++){
				for(j= 0;j < Imagem->colunas;j++){
					fwrite(&Imagem->matriz[i][j],sizeof(int),1,arq);
				}
			}
		}

		//fecha arquivo de escrita
		fclose (arq) ;
		}
		