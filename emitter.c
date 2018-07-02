#include <stdio.h>

#include "sequence.h"

int emit_sequence(const struct frame* firstframe) {
	const struct frame* frame_it = firstframe;
	int index = 0;
	while (frame_it != NULL) {
		while (index > (*frame_it).index) {
			frame_it = (*frame_it).nextframe;
		}
		while (index < (*frame_it).index) {
			putchar('x');
			++index;
		}
		putchar(' ');
		
		for (int i = 0; i < (*frame_it).note_ct; ++i) {
			printf("%s", (*frame_it).notes[i].text);
		}
		
		++index;
		for (int i = 1; i < (*frame_it).duration; ++i) {
			putchar('o');
			++index;
		}
		frame_it = (*frame_it).nextframe;
	}
	putchar('\n');
	return 0;
}
