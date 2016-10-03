# Compilador utilizado
COMP=gcc

# Op��es de compila��o (altere, se desejar outras op��es)
OPCOES_COMP=-c -Wall -std=c99 -lm

# Op��es de liga��o (acrescente, se desejar, alguma op��o)
#OPCOES_LINK=

# Arquivos-fonte (modifique/acrescente)
FONTES=src/main.c src/util.c src/equation.c src/method.c

# A macro a seguir informa que os arquivos-objeto s�o
# obtidos a partir dos arquivos-fonte, substituindo 
# a extens�o .c pela extens�o .o
OBJETOS=$(FONTES:.c=.o)

# Nome do arquivo execut�vel (modifique)
EXECUTAVEL=main

$(EXECUTAVEL): $(OBJETOS)
	$(COMP) $(OPCOES_LINK) $(OBJETOS) -o $@ -lm

util.o: src/util.c src/include/headers.h
	$(COMP) $(OPCOES_COMP) util.c -o util.o

equation.o: src/equation.c src/include/headers.h
	$(COMP) $(OPCOES_COMP) equation.c -o equation.o -lm

method.o: src/method.c src/include/method.h
	$(COMP) $(OPCOES_COMP) method.c -o method.o

limpa:
	-rm -f src/*.o core

reconstroi: limpa main
