ENTRY(main)
MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K

}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
 		*(.text)
 		*(.text.*)
		*(.rodata)
		*(.rodata*)
		_sidata = .;
	} >FLASH
      
       /*load user_progam.o at _userprogram */
       .userprogram 0x0000f000:
       {
          user_program.o
          _sidata = .;
       }
	/* Initialized data will initially be loaded in FLASH at the end of the .text section. */
    .data : AT (_sidata) 
    {
		_sdata = .;
		*(.data)		/* Initialized data */
		_edata = .;
	} >RAM

	.bss : {
		_sbss = .;
		*(.bss)         /* Zero-filled run time allocate data memory */
		_ebss = .;
	} >RAM
    
    _estack = ORIGIN(RAM) + LENGTH(RAM);
 }  
