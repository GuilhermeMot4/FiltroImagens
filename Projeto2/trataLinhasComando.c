// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "acessaImagem.h"
#include "estruturas.h"

char *entrada = NULL;
char *saida = NULL;
double angulo = 90;

//recebe valores da linha de comando para filto negativo
void negativoLC(int argc, char **argv){

  	int option;

	opterr = 0;
	 
	while ((option = getopt (argc, argv, "i:o:")) != -1)
    	switch (option){
      		case 'i':	//arquivo de entrada digitado      
		        entrada = optarg;
		        break;
	      	case 'o':     
		        saida = optarg; //arquivo de saída digitado
		        break;
    	 	default:
	        	perror("Valores inválidos!");
			exit (1) ;
	      }
}

//recebe valores da linha de comando para filto lbp
void lbpLC(int argc, char **argv){

  	int option;

	opterr = 0;
	 
	while ((option = getopt (argc, argv, "i:o:")) != -1)
    	switch (option){
      		case 'i':      //arquivo de entrada digitado   
		        entrada = optarg; 
		        break;
	      	case 'o':     //arquivo de saída digitado   
		        saida = optarg;
		        break;
    	 	default:
	        	perror("Valores inválidos!");
			exit (1) ;
	      }
}

//recebe valores da linha de comando para filto de rotação
void rotacaoLC(int argc, char **argv){

  	int option;

	opterr = 0;
	 
	while ((option = getopt (argc, argv, "a:i:o:")) != -1)
    	switch (option){
    		case 'a':      //ângulo de rotação digitado   
		        angulo = atof(optarg);
		        break;
      		case 'i':      //arquivo de entrada digitado   
		        entrada = optarg;
		        break;
	      	case 'o':     //arquivo de saída digitado   
		        saida = optarg;
		        break;
    	 	default:
	        	perror("Valores inválidos!");
			exit (1) ;
	      }
}