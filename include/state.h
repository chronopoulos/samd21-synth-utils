#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

enum mode_enum {MODE_LIVE, MODE_LOAD, MODE_PLAY, MODE_ARP};
enum arpdir_enum {ARPDIR_DOWN, ARPDIR_UPDOWN, ARPDIR_UP};
enum porta_enum {PORTA_OFF, PORTA_ON, PORTA_AUTO};
enum ctrlMode_enum {CTRL_INTERNAL, CTRL_BOTH, CTRL_EXTERNAL};

struct state_data {

    enum mode_enum mode;
    enum arpdir_enum arpdir;
    enum ctrlMode_enum ctrlMode;

    int transpose_tgl;
    int transpose_btn;

    int portamento1;
    int portamento2;

    bool hold;

};

void state_init(struct state_data *);

#endif
