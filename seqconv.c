#include <stdio.h>

#include "sequence.h"
#include "parser.h"
#include "sorter.h"
#include "emitter.h"

struct frame* firstframe = NULL;

int seqconv() {
	int parse_result = parse_input(&firstframe);
	if (parse_result != 0) {
		fprintf(stderr, "Could not parse input text\n");
		return -1;
	}
	sort_notes(firstframe);
	int emit_result = emit_sequence(firstframe);
	if (emit_result != 0) {
		fprintf(stderr, "An error occurred while emitting sequence\n");
		return -1;
	}
	return 0;
}
