#ifndef ARP_H
#define ARP_H

#include <stdbool.h>

struct arp_data {

    int index;
    bool forward;

};

void arp_init(struct arp_data*);

#endif
