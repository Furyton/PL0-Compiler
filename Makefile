SOURCE_CODE := prog.pas

main: runner.o compiler.o utils.o lex.o synt.o actions.o main.o
	cc -g -o main main.o runner.o compiler.o utils.o lex.o synt.o actions.o

main.o: main.c runner.o compiler.o
	cc -g -c main.c

runner.o: runner.c runner.h def.h PL0.h
	cc -g -c runner.c

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

all: main

run: cleanall all
	./main ${SOURCE_CODE}

clean:
	rm -f main *.o _*

cleanall:
	rm -f -r main *.o _* table.grammar LR_table_gen/__pycache__