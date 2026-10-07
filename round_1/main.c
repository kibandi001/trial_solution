// #include "RTE_Components.h"
// #include CMSIS_device_header

// int main() {
//     for (;;) {
//     }
// }

#include "hc32f030.h"
#include "gpio.h"
#include "sysctrl.h"

// Software delay loop for 48 MHz CPU operation
void delay_ms(uint32_t ms) {
    volatile uint32_t count = ms * 4000;
    while (count--) {
        __NOP();
    }
}

int32_t main(void) {
    stc_gpio_config_t stcGpioCfg;

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    DDL_ZERO_STRUCT(stcGpioCfg);
    stcGpioCfg.enDir = GpioDirOut;         // Output mode
    stcGpioCfg.enDrv = GpioDrvH;           // High drive capability
    stcGpioCfg.enPuPd = GpioNoPuPd;        // No internal pull resistor

    Gpio_Init(GpioPortD, GpioPin2, &stcGpioCfg);

    // Main execution loop
    while (1) {
        Gpio_SetIO(GpioPortD, GpioPin2);   // Drive Pin HIGH (3.3V)
        delay_ms(500);                     // 500 ms delay

        Gpio_ClrIO(GpioPortD, GpioPin2);   // Drive Pin LOW (0V)
        delay_ms(500);                     // 500 ms delay
    }
}
