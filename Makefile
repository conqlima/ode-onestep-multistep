# Compilador utilizado
COMP=gcc

# Opções de compilação (altere, se desejar outras opções)
OPCOES_COMP=-c -Wall -std=c99 -lm

# Opções de ligação (acrescente, se desejar, alguma opção)
#OPCOES_LINK=

# Arquivos-fonte (modifique/acrescente)
FONTES=src/main.c src/util.c src/equation.c src/method.c

# A macro a seguir informa que os arquivos-objeto são
# obtidos a partir dos arquivos-fonte, substituindo 
# a extensão .c pela extensão .o
OBJETOS=$(FONTES:.c=.o)

# Nome do arquivo executável (modifique)
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
