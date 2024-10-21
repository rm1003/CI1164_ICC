#########################################
#   Ruibin Mei							#
#   GRR20232358							#
#										#
#   Makefile							#
#########################################

# PROGRAMA
    PROG = inversa
	ARQUIVOS = inversa.c utils.c sl.c io.c lu.c
    OBJS = $(ARQUIVOS:.c=.o)

# Compilador
    CC     = gcc

# Acrescentar onde apropriado as opções para incluir uso da biblioteca LIKWID
    CFLAGS = -O0 -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
    LFLAGS = -lm -llikwid

# Lista de arquivos para distribuição. Acrescentar mais arquivos se necessário.
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -L${LIKWID_LIB} $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) $(OBJS) core a.out $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
