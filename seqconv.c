#include <stdio.h>

#include "sequence.h"
#include "parser.h"

struct frame* firstframe = NULL;

int seqconv() {
	int parse_result = parse_input(&firstframe);
	if (parse_result != 0) {
		fprintf(stderr, "Could not parse input text\n");
		return -1;
	}
	return 0;
}
