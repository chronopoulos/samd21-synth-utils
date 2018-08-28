#ifndef SEQ_H
#define SEQ_H

#include "stdint.h"

#define SEQ_MAXLEN 128
#define SEQ_BUFFER_SIZE 512

struct seq_data {

    uint8_t len;
    uint8_t ridx;
    uint8_t widx;

    uint8_t notes[SEQ_MAXLEN]; // TODO account for negative notes? int8_t?
    uint8_t legatos[SEQ_MAXLEN];
    uint8_t rests[SEQ_MAXLEN];

};

void seq_init(struct seq_data*);
void seq_serialize(struct seq_data*, uint8_t*);
void seq_deserialize(struct seq_data*, uint8_t*) ;
void seq_append_note(struct seq_data*, uint32_t );
void seq_append_legato(struct seq_data*, uint32_t );
void seq_append_rest(struct seq_data*);

#endif
