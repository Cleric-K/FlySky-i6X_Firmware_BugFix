PREFIX = arm-none-eabi-
CC := ${PREFIX}gcc
LD := ${PREFIX}ld
OBJCOPY := ${PREFIX}objcopy
FLAGS = -mthumb -mcpu=cortex-m0


FW_ORIG := org.bin
FW_ELF := fs.elf
FW_COMPLETE_BIN := ../build/FS-I6X_with_bootloader.bin
FW_UPDATE_BIN := ../build/FS-I6X.bin

OBJECTS := hooks.o chan_hack.o

all: ${FW_UPDATE_BIN}

${FW_UPDATE_BIN}: link.ld ${OBJECTS}
	${LD} -T link.ld ${OBJECTS} -o ${FW_ELF}
	${OBJCOPY} ${FW_ELF} --update-section .org_fw=${FW_ORIG} --set-section-flags .org_fw=alloc
	${OBJCOPY} -O binary ${FW_ELF} ${FW_COMPLETE_BIN}
	python fs-i6x.py ${FW_COMPLETE_BIN} ${FW_UPDATE_BIN}

%.o: %.s
	${CC} ${FLAGS} -c $<

%.o: %.c
	${CC} ${FLAGS} -c -Os $<

clean:
	rm -f ${OBJECTS} ${FW_ELF} ${FW_COMPLETE_BIN} ${FW_UPDATE_BIN}
