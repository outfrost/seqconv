compileargs ::= -g -Wall -Wextra -Wpedantic
linkargs ::=
libraries ::=
objects ::= $(addprefix out/,\
              main.o seqconv.o parser.o sorter.o emitter.o)

# Set executable extension for the platform
ifeq ($(OS),Windows_NT)
	binext ::= .exe
else
	binext ::=
endif
binary ::= out/seqconv$(binext)
# ######

$(binary) : $(objects) | out
	@echo "###### Linking executable..."
	$(CC) $(linkargs) -o $(binary) $(objects) $(libraries)

seqconv : $(binary)

run : $(binary)
	@echo
	$(binary)

init : out

out :
	mkdir out/

out/main.o : main.c seqconv.h | out
	$(CC) $(compileargs) -c -o out/main.o main.c

out/seqconv.o : seqconv.c sequence.h parser.h emitter.h | out
	$(CC) $(compileargs) -c -o out/seqconv.o seqconv.c

out/parser.o : parser.c sequence.h parser_.h | out
	$(CC) $(compileargs) -c -o out/parser.o parser.c

out/sorter.o : sorter.c sequence.h | out
	$(CC) $(compileargs) -c -o out/sorter.o sorter.c

out/emitter.o : emitter.c sequence.h | out
	$(CC) $(compileargs) -c -o out/emitter.o emitter.c

.PHONY : seqconv run init
