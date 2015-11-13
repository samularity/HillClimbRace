#==========================
#
#  makefile for atmega32u4
#
#  2015.11 - Samuel Munz
# 
#==========================

#==========================
all: 
	avr-gcc  -funsigned-char -funsigned-bitfields -DF_CPU=16000000  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32u4 -c -std=gnu99 -MD -MP -MF "main.d" -MT"main.d" -MT"main.o"   -o "main.o" "main.c"
	avr-gcc -o hillclimb.elf  main.o   -Wl,-Map="hillclimb.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Wl,--defsym=__stack=0xa00 -mmcu=atmega32u4 
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "hillclimb.elf" "hillclimb.hex"
	avr-objcopy -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "hillclimb.elf" "hillclimb.eep" || exit 0
	avr-objdump -h -S "hillclimb.elf" > "hillclimb.lss"
	avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature  "hillclimb.elf" "hillclimb.srec"
#==========================

#-------------------
clean:
	rm -f *.o *.map *.out *.hex *.elf *.lss *.eep *.d *.srec
#-------------------