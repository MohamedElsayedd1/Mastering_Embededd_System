
### Lab Report: UART0 Communication on ARM VersatilePB Board

**Objective:** To develop and simulate a bare-metal application on the ARM VersatilePB platform that sends the string "Learn-In-Depth: Mohamed Elsayed" via UART0.

#### **1. Environment Setup**

- **Toolchain:** GNU ARM Cross Toolchain  
  Installed the ARM toolchain to compile, assemble, and link the source code.
  
- **QEMU Emulator:**  
  Used QEMU to emulate the ARM VersatilePB board for testing the application.

#### **2. Source Files**

- **App.c:** Contains the main function, which initializes the UART0 and sends the string.
- **UART.c:** Implements the UART driver to handle communication.
- **Startup.s:** Assembly code for the startup routine, setting up the stack and initializing the system.
- **Linker Script (linker_script.ld):** Defines memory regions and specifies the memory layout for the application.

#### **3. Compilation and Linking**

The following commands were used to compile, assemble, and link the application:

1. **Compilation:**  
   Compiled the C source files into object files:
   ```bash
   arm-none-eabi-gcc -c -g -mcpu=arm926ej-s -I . App.c -o App.o
   arm-none-eabi-gcc -c -g -mcpu=arm926ej-s -I . UART.c -o UART.o
   ```
   
2. **Assembly:**  
   Assembled the startup assembly code:
   ```bash
   arm-none-eabi-gcc -c -g -mcpu=arm926ej-s -I . startup.s -o startup.o
   ```

3. **Linking:**  
   Linked the object files to create an ELF file:
   ```bash
   arm-none-eabi-ld -T linker_script.ld -Map=App.map App.o UART.o startup.o -o App.elf
   ```

4. **Binary Conversion:**  
   Converted the ELF file to a binary file suitable for loading into the emulator:
   ```bash
   arm-none-eabi-objcopy -O binary App.elf App.bin
   ```

#### **4. Debugging and Analysis**

- **Object Dump:**
   - Examined the section headers and symbol information in the object files and ELF file using:
     ```bash
     arm-none-eabi-objdump -h App.o
     arm-none-eabi-objdump -h UART.o
     arm-none-eabi-objdump -h startup.o
     arm-none-eabi-objdump -h App.elf
     ```
   - Verified the contents and sections such as `.text`, `.data`, and `.bss`.

- **Symbol Table:**
   - Inspected the symbol tables for debugging:
     ```bash
     arm-none-eabi-nm App.o
     arm-none-eabi-nm UART.o
     arm-none-eabi-nm startup.o
     arm-none-eabi-nm App.elf
     ```

#### **5. Simulation**

- **Running on QEMU:**
  Simulated the application on the ARM VersatilePB board using QEMU:
  ```bash
  qemu-system-arm -M versatilepb -m 128M -nographic -kernel "C:\Users\Dubai Store\Desktop\Lab1\App.bin"
  ```
  - Verified that the string "Learn-In-Depth: Mohamed Elsayed" was transmitted correctly via UART0.

#### **6. Conclusion**

The lab successfully demonstrated how to create a bare-metal application for the ARM VersatilePB platform. The application was able to send the specified string through UART0, confirming that the startup code, linker script, and UART driver were correctly implemented and configured.

Report Link : https://drive.google.com/file/d/1-HRO37fxw9MPW3nOmO-VWH2jLgagex4s/view?usp=drive_link
