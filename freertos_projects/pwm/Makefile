# GNU ARM Embedded Toolchain path
TOOLS_DIR = /home/akn/opt/gcc-arm-none-eabi-6-2017-q2-update/bin
CC=$(TOOLS_DIR)/arm-none-eabi-gcc
LD=$(TOOLS_DIR)/arm-none-eabi-ld
AR=$(TOOLS_DIR)/arm-none-eabi-ar
AS=$(TOOLS_DIR)/arm-none-eabi-as
CP=$(TOOLS_DIR)/arm-none-eabi-objcopy
OD=$(TOOLS_DIR)/arm-none-eabi-objdump
SIZE=$(TOOLS_DIR)/arm-none-eabi-size

# Define directories
BINDIR=bin
SRCDIR=src

# Find source files
ASOURCES=$(shell find -L $(SRCDIR) -name '*.s')
CSOURCES+=$(shell find -L $(SRCDIR) -name '*.c')
# Find header directories
INC=$(shell find -L . -name '*.h' -exec dirname {} \; | uniq)
INCLUDES=$(INC:%=-I%)
# Create object list
OBJECTS=$(ASOURCES:%.s=%.o)
OBJECTS+=$(CSOURCES:%.c=%.o)

# Output files
BINELF=out.elf
BINHEX=out.hex
BINRAW=out.bin

# MCU FLAGS
MCFLAGS=-mcpu=cortex-m4 -mthumb -mlittle-endian \
-mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork
# COMPILE FLAGS
DEFS=-DUSE_STDPERIPH_DRIVER -DSTM32F4XX
CFLAGS  =-c $(MCFLAGS) $(DEFS) $(INCLUDES)
# LINKER FLAGS
LDSCRIPT= stm32_flash.ld
LDFLAGS =-T $(LDSCRIPT) --specs=nosys.specs $(MCFLAGS)

# Build Rules
all: $(BINDIR)/$(BINRAW) $(BINDIR)/$(BINHEX)

$(BINDIR)/$(BINRAW): $(BINDIR)/$(BINELF)
	$(CP) -O binary $< $@
	@echo "Objcopy from ELF to BIN complete!\n"

$(BINDIR)/$(BINHEX): $(BINDIR)/$(BINELF)
	$(CP) -O ihex $< $@
	@echo "Objcopy from ELF to IHEX complete!\n"

$(BINDIR)/$(BINELF): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo "Linking complete!\n"
	$(SIZE) $(BINDIR)/$(BINELF)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	@echo "Compiled "$<"!\n"

%.o: %.s
	$(CC) $(CFLAGS) $< -o $@
	@echo "Assambled "$<"!\n"

clean:
	rm -f $(OBJECTS) $(BINDIR)/$(BINELF) $(BINDIR)/$(BINHEX) $(BINDIR)/$(BINRAW)
