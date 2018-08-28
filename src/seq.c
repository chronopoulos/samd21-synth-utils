/*
Copyright (c) 2018 Chris Chronopoulos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "seq.h"

void seq_init(struct seq_data *data) {

    data->len = 0;
    data->ridx = 0;
    data->widx = 0;
    for (int i=0; i<SEQ_MAXLEN; i++) {
        data->notes[i] = 0;
        data->rests[i] = 0;
        data->legatos[i] = 0;
    }

}

void seq_serialize(struct seq_data *data, uint8_t *buffer) {

    int i;
    int idx = 0;

    buffer[idx] = data->len;
    idx++;

    for (i=0; i<SEQ_MAXLEN; i++) {
        buffer[idx] = data->notes[i];
        idx++;
    }

    for (i=0; i<SEQ_MAXLEN; i++) {
        buffer[idx] = data->legatos[i];
        idx++;
    }

    for (i=0; i<SEQ_MAXLEN; i++) {
        buffer[idx] = data->rests[i];
        idx++;
    }

}

void seq_deserialize(struct seq_data *data, uint8_t *buffer) {

    int i;
    int idx = 0;

    data->len = buffer[idx];
    idx++;

    for (i=0; i<SEQ_MAXLEN; i++) {
        data->notes[i] = buffer[idx];
        idx++;
    }

    for (i=0; i<SEQ_MAXLEN; i++) {
        data->legatos[i] = buffer[idx];
        idx++;
    }

    for (i=0; i<SEQ_MAXLEN; i++) {
        data->rests[i] = buffer[idx];
        idx++;
    }

    data->ridx = 0;
    data->widx = 0;

}

void seq_append_note(struct seq_data *data, uint32_t note) {

    if (data->len < SEQ_MAXLEN) {
        data->notes[data->len] = note;
        data->len++;
    }

}

void seq_append_legato(struct seq_data *data, uint32_t note) {

    if (data->len < SEQ_MAXLEN) {
        data->notes[data->len] = note;
        data->legatos[data->len] = 1;
        data->len++;
    }

}

void seq_append_rest(struct seq_data *data) {

    if (data->len < SEQ_MAXLEN) {
        data->rests[data->len] = 1;
        data->len++;
    }

}
