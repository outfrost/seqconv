#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "sequence.h"
#include "parser_.h"

int parse_input(struct chord** dest) {
	struct chord* firstchord = NULL;
	
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
				if (head == '#') {
					head = 's';
				}
				
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
				struct chord** chord_it = &firstchord;
				bool inserted = false;
				while (!inserted
						&& *chord_it != NULL
						&& (**chord_it).index <= index) {
					if ((**chord_it).index == index) {
						++(**chord_it).note_ct;
						(**chord_it).notes = realloc((**chord_it).notes,
								(**chord_it).note_ct * sizeof(struct note));
						(**chord_it).notes[(**chord_it).note_ct - 1] = newnote;
						if (duration > (**chord_it).duration) {
							(**chord_it).duration = duration;
						}
						inserted = true;
					}
					chord_it = &(**chord_it).nextchord;
				}
				if (!inserted) {
					struct chord* newchord = malloc(sizeof(struct chord));
					(*newchord) = (struct chord){ .index = index,
					                              .duration = duration,
					                              .note_ct = 1,
					                              .notes = malloc(sizeof(struct note)),
					                              .nextchord = *chord_it };
					(*newchord).notes[0] = newnote;
					*chord_it = newchord;
				}
				state = LOOKING;
			}
		}
	}
	*dest = firstchord;
	return 0;
}

bool is_notechar(const int c) {
	return isalnum(c) || c == '#';
}
