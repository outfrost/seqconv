compileargs = -Wall -Wextra -Wpedantic
linkargs = 
objects = out/main.o out/seqconv.o out/parser.o

out/seqconv : $(objects)
	@echo "###### Linking executable..."
	cc -o out/seqconv $(objects) $(linkargs)

seqconv : out/seqconv

run : out/seqconv
	@echo
	out/seqconv

init : out/

out/ :
	mkdir out/

out/main.o : main.c seqconv.h
	cc -c -o out/main.o main.c $(compileargs)

out/seqconv.o : seqconv.c sequence.h parser.h
	cc -c -o out/seqconv.o seqconv.c $(compileargs)

out/parser.o : parser.c sequence.h parser_.h
	cc -c -o out/parser.o parser.c $(compileargs)
