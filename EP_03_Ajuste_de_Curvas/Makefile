# PROGRAMA
    PROG = ajustePolV1 ajustePolV2 gera_entrada

# Compilador
    CC     = gcc
    CFLAGS = -O3 -mavx -march=native -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
    LFLAGS = -lm -L${LIKWID_LIB} -llikwid

# Lista de arquivos para distribuição.
# LEMBRE-SE DE ACRESCENTAR OS ARQUIVOS ADICIONAIS SOLICITADOS NO ENUNCIADO DO TRABALHO
DISTFILES = *.c *.h LEIAME* Makefile 
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

ajustePolV1: ajustePolV1.c utils.c
	gcc -o $@ $(CFLAGS) $^ $(LFLAGS)

ajustePolV2: ajustePolV2.c utils.c
	gcc -o $@ $(CFLAGS) $^ $(LFLAGS)

gera_entrada: gera_entrada.c
	gcc -o $@ $^ -lm

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak core 

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
