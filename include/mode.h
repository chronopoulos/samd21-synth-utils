#ifndef MODE_H
#define MODE_H

#include <stdbool.h>

#define PORTAMENTO_MODE_OFF 0
#define PORTAMENTO_MODE_ON 1
#define PORTAMENTO_MODE_AUTO 2

#define MODE_ARP_OFF 0
#define MODE_ARP_DOWN 1
#define MODE_ARP_UPDOWN 2
#define MODE_ARP_UP 3

struct mode_data {

    int portamento1;
    int portamento2;

    int arp;

    bool load;
    bool play;

    bool hold;

    int transpose_tgl;
    int transpose_btn;

};

void mode_init(struct mode_data*);
void mode_set_portamento1(struct mode_data*, int);
void mode_set_portamento2(struct mode_data*, int);
void mode_toggle_load(struct mode_data*);
void mode_toggle_play(struct mode_data*);
void mode_set_arp(struct mode_data *data, int mode);

#endif
