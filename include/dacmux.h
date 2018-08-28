#include <dac.h>
#include <port.h>

#define DACMUX_SEL1_PIN PIN_PA23
#define DACMUX_SEL2_PIN PIN_PA22
#define DACMUX_SEL3_PIN PIN_PA21
#define DACMUX_INHB_PIN PIN_PA20

#define DAC_SETTLE_NCYCLES 100 // TODO tune this

struct dacmux_data {

    struct dac_module instance;

    uint16_t cv1;
    uint16_t range;
    uint16_t random;
    uint16_t accel;

};

void dacmux_init(struct dacmux_data*);
void dacmux_set_cv1(struct dacmux_data*, uint16_t);
void dacmux_set_range(struct dacmux_data *data, uint16_t);
void dacmux_set_random(struct dacmux_data *data, uint16_t);
void dacmux_set_accel(struct dacmux_data *data, uint16_t);
void dacmux_output(struct dacmux_data *data);
