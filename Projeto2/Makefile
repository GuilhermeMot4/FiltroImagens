#Nome: Guilherme Ferreira Mota 
#GRR: 20197268
#Makefile

CFLAGS = -Wall
LDLIBS = -lm
objects = trataImagem.c acessaImagem.c trataLinhasComando.c

#gera todos os executáveis
all: pgm

pgm: pgmnega pgmlbp pgmrotacao

#executável do filtro negativo
pgmnega: pgmnega.c $(objects)
	cc pgmnega.c -o pgmnega $(objects) $(LDLIBS)

#executável do filtro lbp
pgmlbp: pgmlbp.c $(objects)
	cc pgmlbp.c -o pgmlbp $(objects) $(LDLIBS)

#executável do filtro de rotação
pgmrotacao: pgmrotacao.c $(objects)
	cc pgmrotacao.c -o pgmrotacao $(objects) $(LDLIBS)
#limpeza dos arquivos
clean:
	-rm -f *~ *.o *pgm
purge: clean
	-rm -f pgmnega pgmlbp pgmrotacao