#include <stdio.h>

#include "sequence.h"
#include "parser.h"
#include "sorter.h"
#include "emitter.h"

struct chord* firstchord = NULL;

int seqconv() {
	int parse_result = parse_input(&firstchord);
	if (parse_result != 0) {
		fprintf(stderr, "Could not parse input text\n");
		return -1;
	}
	sort_notes(firstchord);
	int emit_result = emit_sequence(firstchord);
	if (emit_result != 0) {
		fprintf(stderr, "An error occurred while emitting sequence\n");
		return -1;
	}
	return 0;
}
