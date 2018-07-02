#include <stdio.h>

#include "sequence.h"

int emit_sequence(const struct chord* firstchord) {
	const struct chord* chord_it = firstchord;
	int index = 0;
	while (chord_it != NULL) {
		while (index > (*chord_it).index) {
			chord_it = (*chord_it).nextchord;
		}
		while (index < (*chord_it).index) {
			putchar('x');
			++index;
		}
		putchar(' ');
		
		for (int i = 0; i < (*chord_it).note_ct; ++i) {
			printf("%s", (*chord_it).notes[i].text);
		}
		
		++index;
		for (int i = 1; i < (*chord_it).duration; ++i) {
			putchar('o');
			++index;
		}
		chord_it = (*chord_it).nextchord;
	}
	putchar('\n');
	return 0;
}
