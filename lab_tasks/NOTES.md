# Notes

## Serial Connection

The design of the Board does not allow for USART2 Serial Connection via USB.
According to the user manual, either manual soldering or a seprate USART to USB dongle is needed on the pins `PA2` and `PA3`.

https://stackoverflow.com/questions/51825483/serial-communications-over-stlink-with-stm32f4discovery-is-it-possible

### Set up Azure RTOS ThreadX

https://community.st.com/t5/stm32-mcus/how-can-i-add-tracex-support-in-stm32cubeide/ta-p/49380
