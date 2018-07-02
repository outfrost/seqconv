#include <stdbool.h>
#include <stddef.h>

#include "sequence.h"

void sort_notes(struct frame* firstframe) {
	struct frame* frame_it = firstframe;
	while (frame_it != NULL) {
		bool sorted = false;
		while (!sorted) {
			sorted = true;
			for (int i = 0; i < (*frame_it).note_ct - 1; ++i) {
				// this assumes there's at least a null byte
				// in every note string
				bool compared = false;
				for (int k = 0; !compared; ++k) {
					if ((*frame_it).notes[i].text[k]
							> (*frame_it).notes[i+1].text[k]) {
						struct note temp = (*frame_it).notes[i];
						(*frame_it).notes[i] = (*frame_it).notes[i+1];
						(*frame_it).notes[i+1] = temp;
						compared = true;
						sorted = false;
					}
					else if ((*frame_it).notes[i].text[k]
							< (*frame_it).notes[i+1].text[k]) {
						compared = true;
					}
					
					if ((*frame_it).notes[i].text[k] == '\0') {
						compared = true;
					}
				}
			}
		}
		frame_it = (*frame_it).nextframe;
	}
}
