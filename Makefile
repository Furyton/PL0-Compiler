SOURCE_CODE := prog.pas

compiler: compiler.o utils.o lex.o synt.o actions.o
	cc -g -o compiler compiler.o utils.o lex.o synt.o actions.o

compiler.o: compiler.c def.h
	cc -g -c compiler.c

utils.o: utils.c def.h
	cc -g -c utils.c

lex.o: lex.c def.h
	cc -g -c lex.c

def.h: PL0.h

synt.o: synt.c def.h  grammar.h table.grammar actions.o
	cc -g -c synt.c

actions.o: actions.c def.h grammar.h
	cc -g -c actions.c

table.grammar: LR_table_gen/grammar
	python3 LR_table_gen/LR_table.py "LR_table_gen/grammar" > table.grammar

all: compiler

run: cleanall all
	./compiler ${SOURCE_CODE} > _info

clean:
	rm -f compiler *.o _*

cleanall:
	rm -f -r compiler *.o _* table.grammar LR_table_gen/__pycache__