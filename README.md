# stm32f4-discovery
Learning ARM Cortex-M4 programming using STM32F4 discovery board and GNU Embedded Toolchain for ARM.

Steps to setup a development environment for STM32F4 discovery board on linux(openSUSE) as found on this [webpage][1]:

Step 1: Install a toolchain,
there are two options, for bare metal target - ‘GCC ARM Embedded Toolchain’ and
for GNU/Linux target - ‘Linaro’. 
Going with the 1st option, steps to install it on linux are on [this][2] page at the very bottom.
The instructions have package names for ubuntu, for [openSUSE][3] use:

	sudo zypper -n install autoconf m4 automake libtool patch make makeinfo flex bison termcap ncurses-devel mpfr-devel gmp-devel mpc-devel gcc-c++
Download toolchain from [here][4]. This is a precompiled toolchain(just extract and deny write permission).

Step 2: Install segger j-link or [openocd][6](there’s an [option][5] to convert swd on stm32 board to j-link).

Step 3: Install [QEMU][12], java, [eclipse][7] and [packs-manager][8].

Step 4: Install stlink(either clone and build from [this github repo][9] or use the one packaged for your distro, like [this][10] one for openSUSE)

Step 5: Start eclipse and follow these steps to create a [new project][11]. By default the generated makefile 	creates a ihex hex file for flash which did not work for me so right-click the project and go into 	properties, find →’C/C++ Build’ → ‘Settings’ → Tool Settings (tab).  In that tab find ‘GNU 	ARM Cross Create Flash Image’ → ‘General’: Change Output file format (-O) to ‘Raw binary’.

Step 6: Build and Run to emulate using qemu, flash using:

	st-flash write projectname.bin 0x8000000

[1]:https://gnu-mcu-eclipse.github.io/install/
[2]:https://gnu-mcu-eclipse.github.io/toolchain/arm/install/
[3]:http://twoerner.blogspot.com/2014/01/building-gcc-arm-embedded-on-opensuse.html
[4]:https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads
[5]:https://gnu-mcu-eclipse.github.io/developer/j-link-stm32-boards/
[6]:https://github.com/gnu-mcu-eclipse/openocd/releases
[7]:https://github.com/gnu-mcu-eclipse/org.eclipse.epp.packages/releases/
[8]:https://gnu-mcu-eclipse.github.io/plugins/packs-manager/
[9]:https://github.com/texane/stlink
[10]:https://software.opensuse.org/package/stlink
[11]:https://gnu-mcu-eclipse.github.io/tutorials/blinky-arm/
[12]:https://gnu-mcu-eclipse.github.io/qemu/install/
