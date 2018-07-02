#include <stdbool.h>
#include <stddef.h>

#include "sequence.h"

void sort_notes(struct chord* firstchord) {
	struct chord* chord_it = firstchord;
	while (chord_it != NULL) {
		bool sorted = false;
		while (!sorted) {
			sorted = true;
			for (int i = 0; i < (*chord_it).note_ct - 1; ++i) {
				// this assumes there's at least a null byte
				// in every note string
				bool compared = false;
				for (int k = 0; !compared; ++k) {
					if ((*chord_it).notes[i].text[k]
							> (*chord_it).notes[i+1].text[k]) {
						struct note temp = (*chord_it).notes[i];
						(*chord_it).notes[i] = (*chord_it).notes[i+1];
						(*chord_it).notes[i+1] = temp;
						compared = true;
						sorted = false;
					}
					else if ((*chord_it).notes[i].text[k]
							< (*chord_it).notes[i+1].text[k]) {
						compared = true;
					}
					
					if ((*chord_it).notes[i].text[k] == '\0') {
						compared = true;
					}
				}
			}
		}
		chord_it = (*chord_it).nextchord;
	}
}
