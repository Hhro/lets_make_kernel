/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(_start)
 
/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 1M;
 
	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.boottext :
	{
		*(.multiboot)
		*(.text)
	}
 
	/* Read-only data. */
	.bootrodata :
	{
		*(.rodata)
	}
 
	/* Read-write data (initialized) */
	.bootdata :
	{
		*(.data)
	}
 
	/* Read-write data (uninitialized) and stack */
	.bootbss :
	{
		*(.bss)
		*(COMMON)
	}
	
	. = ALIGN(0x1000);
	_boot_end = .;
 
	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}