# lextest: driver.o lex.yy.o errormsg.o util.o
# 	cc -g -o lextest driver.o lex.yy.o errormsg.o util.o

# driver.o: driver.c tokens.h errormsg.h util.h
# 	cc -g -c driver.c

# errormsg.o: errormsg.c errormsg.h util.h
# 	cc -g -c errormsg.c

# lex.yy.o: lex.yy.c tokens.h errormsg.h util.h
# 	cc -g -c lex.yy.c

# lex.yy.c: tiger.lex
# 	lex tiger.lex

# util.o: util.c util.h
# 	cc -g -c util.c

# clean: 
# 	rm -f a.out util.o driver.o lex.yy.o lex.yy.c errormsg.o

SOURCE_CODE := prog.pas

compiler: compiler.o utils.o lex.o synt.o
	cc -g -o compiler compiler.o utils.o lex.o synt.o

compiler.o: compiler.c def.h
	cc -g -c compiler.c

utils.o: utils.c def.h
	cc -g -c utils.c

lex.o: lex.c def.h
	cc -g -c lex.c

synt.o: synt.c def.h table.grammar
	cc -g -c synt.c

table.grammar:
	python3 LR_table_gen/LR_table.py "LR_table_gen/grammar" > table.grammar

all: compiler

run: all
	./compiler ${SOURCE_CODE}

clean:
	rm -f compiler *.o _*

cleanall:
	rm -f -r compiler *.o _* table.grammar LR_table_gen/__pycache__