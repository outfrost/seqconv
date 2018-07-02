#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "sequence.h"
#include "parser_.h"

int parse_input(struct frame** dest) {
	struct frame* firstframe = NULL;
	
	enum scanstate state = LOOKING_FOR_BRACES;
	int braces = 0;
	int index;
	int duration;
	int dummy;
	struct note newnote;
	
	int head = '\0';
	while (head != EOF) {
		if (state == LOOKING_FOR_BRACES) {
			head = getchar();
			if (head == '{') {
				++braces;
				state = IN_BRACES;
			}
		}
		else if (state == IN_BRACES) {
			head = getchar();
			if (head == '{') {
				++braces;
			}
			else if (head == '}') {
				--braces;
				if (braces == 0) {
					state = LOOKING;
				}
			}
		}
		else if (state == LOOKING) {
			if (scanf("%d", &index) == EOF) {
				head = EOF;
			}
			else {
				state = FOUND_INDEX;
			}
		}
		else if (state == FOUND_INDEX) {
			head = getchar();
			if (isspace(head)) {
				state = FOUND_INDEX_SPACE;
			}
			else {
				state = LOOKING;
			}
		}
		else if (state == FOUND_INDEX_SPACE) {
			head = getchar();
			if (is_notechar(head)) {
				newnote.text = calloc(2, sizeof(char));
				newnote.text[0] = head;
				state = FOUND_NOTE;
			}
			else if (!isspace(head)) {
				state = LOOKING;
			}
		}
		else if (state == FOUND_NOTE) {
			head = getchar();
			if (is_notechar(head)) {
				int text_len = strlen(newnote.text) + sizeof(char);
				char* newtext = malloc(text_len + sizeof(char));
				strncpy(newtext, newnote.text, text_len);
				newtext[text_len - sizeof(char)] = head;
				newtext[text_len] = '\0';
				free(newnote.text);
				newnote.text = newtext;
			}
			else if (isspace(head)) {
				state = FOUND_NOTE_SPACE;
			}
		}
		else if (state == FOUND_NOTE_SPACE) {
			if (scanf("%d", &duration) == EOF) {
				free(newnote.text);
				head = EOF;
			}
			else {
				state = FOUND_DURATION;
			}
		}
		else if (state == FOUND_DURATION) {
			head = getchar();
			if (isspace(head)) {
				state = FOUND_DURATION_SPACE;
			}
			else {
				free(newnote.text);
				state = LOOKING;
			}
		}
		else if (state == FOUND_DURATION_SPACE) {
			if (scanf("%d", &dummy) == EOF) {
				free(newnote.text);
				head = EOF;
			}
			else {
				struct frame** frame_it = &firstframe;
				bool inserted = false;
				while (!inserted
				       && *frame_it != NULL
				       && (**frame_it).index <= index) {
					if ((**frame_it).index == index) {
						++(**frame_it).note_ct;
						(**frame_it).notes = realloc((**frame_it).notes,
								(**frame_it).note_ct * sizeof(struct note));
						(**frame_it).notes[(**frame_it).note_ct - 1] = newnote;
						if (duration > (**frame_it).duration) {
							(**frame_it).duration = duration;
						}
						inserted = true;
					}
					frame_it = &(**frame_it).nextframe;
				}
				if (!inserted) {
					struct frame* newframe = malloc(sizeof(struct frame));
					(*newframe).index = index;
					(*newframe).duration = duration;
					(*newframe).note_ct = 1;
					(*newframe).notes = malloc(sizeof(struct note));
					(*newframe).nextframe = *frame_it;
					*frame_it = newframe;
				}
				state = LOOKING;
			}
		}
	}
	*dest = firstframe;
	return 0;
}

bool is_notechar(const int c) {
	return isalnum(c) || c == '#';
}
