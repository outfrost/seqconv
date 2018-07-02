#ifndef SEQUENCE_H_
#define SEQUENCE_H_

struct note {
	char* text;
};

struct frame {
	int index;
	int duration;
	int note_ct;
	struct note* notes;
	struct frame* nextframe;
};

#endif
