# custom-keypad
Utilized KiCAD and STM32Cube to design a keypad pre-programmed with 6 specific key bindings and a volume knob. <br>
Powered by a STM32H7A3RGT6 microcontroller with Cherry MX Brown Switches and a knurled metal volume knob. <br>
Enclosed the PCB with a custom black 3D printed case to improve the appearance, saftey, and stabliity of the device. <br> <br>
Used consumer and keypad hardware interface device reports to create a custom HID report that was able to send both media and regular keyboard commands to PCs. 
Created a decoder + EXTI interrupt system to properly debounce and evaluate transistions in the rotary encoder to effectively adjust volume corresponding to the end user's turning of the dial. <br>
