SOURCE_CODE := prog.pas

compiler: compiler.o utils.o lex.o synt.o
	cc -g -o compiler compiler.o utils.o lex.o synt.o

compiler.o: compiler.c def.h
	cc -g -c compiler.c

utils.o: utils.c def.h
	cc -g -c utils.c

lex.o: lex.c def.h
	cc -g -c lex.c

synt.o: synt.c def.h  grammar.h table.grammar
	cc -g -c synt.c

table.grammar: LR_table_gen/grammar
	python3 LR_table_gen/LR_table.py "LR_table_gen/grammar" > table.grammar

all: compiler

run: cleanall all
	./compiler ${SOURCE_CODE}

clean:
	rm -f compiler *.o _*

cleanall:
	rm -f -r compiler *.o _* table.grammar LR_table_gen/__pycache__ errmsg.err