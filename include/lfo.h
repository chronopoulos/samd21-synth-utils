#include <port.h>
#include <extint.h>
#include <extint_callback.h>
#include <system_interrupt.h>

#define LFO_CLK_PIN PIN_PA15 // this is the input
#define LFO_CLK_EXTINT_PIN PIN_PA15A_EIC_EXTINT15 
#define LFO_CLK_EXTINT_MUX MUX_PA15A_EIC_EXTINT15 
#define LFO_EXTINT_CHAN 15

#define LFO_RESET_PIN PIN_PA16 // this is the output


void lfo_init(void);
void lfo_register_callback(const extint_callback_t cb);
void lfo_enable(void);
void lfo_disable(void);
void lfo_reset(void);

