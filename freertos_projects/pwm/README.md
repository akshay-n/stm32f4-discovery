The goal here is to enable PWM on stm32f4. This project has four tasks, each drives a LED using different channels of TIMER4 as a PWM source. The tasks are synchronized by a binary semaphore such that the LEDs 'fade in and out' one after the other instead doing so together.

```
make clean
make -j4
st-flash write bin/out.bin 0x8000000
