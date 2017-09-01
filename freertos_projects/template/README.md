This is simple project that uses the freeRTOS kernel to blink LEDs on the board.
It can be used as a template. The hard part was integrating the kernel with the stm32f4 firmware.

```
make clean
make -j4
st-flash write bin/out.bin 0x8000000
