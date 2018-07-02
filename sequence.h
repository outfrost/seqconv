#ifndef SEQUENCE_H_
#define SEQUENCE_H_

struct note {
	char* text;
};

struct chord {
	int index;
	int duration;
	int note_ct;
	struct note* notes;
	struct chord* nextchord;
};

#endif
