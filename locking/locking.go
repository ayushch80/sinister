package locking

import (
	"fmt"
	"log"
	"debug/elf"
	"sinister/utils"
)

func LockBinary(filepath string, data *[]byte) {
	// Read the file
	fmt.Println("[*] Reading the file")
	ELF, err := elf.Open(filepath)
	if err != nil {
		log.Fatalf("[-] Failed while reading ELF file at : %s\n", filepath)
	}

	// Check ELF for 64-bit format
	if ELF.FileHeader.Class != elf.ELFCLASS64 {
		log.Fatalf("[-] Currently only 64-bit binaries are supported.")
	}

	// METHOD 1
	// Doesn't affect much but kind of encrypts the Section Header Table
	// Nearly same as stripped binaries
	// Change the e_shoff, e_shnum, e_shstrndx
	copy((*data)[40:], utils.GenerateGibberish(8)) // e_shoff
	copy((*data)[60:], utils.GenerateGibberish(2)) // e_shnum
	copy((*data)[62:], utils.GenerateGibberish(2)) // e_shstrndx
	// The amount of identified functions decreases significantly


	// METHOD 2
	// Replace '.symtab' and '.strtab' with gibberish
	var symtabOffset, strtabOffset uint64
	var symtabSize, strtabSize int
	{
		symtab := ELF.Section(".symtab")
		if symtab == nil {
			log.Fatalf("[-] Unable to locate '.symtab'\n")
		}

		strtab := ELF.Section(".strtab")
		if symtab == nil {
			log.Fatalf("[-] Unable to locate '.strtab'\n")
		}

		symtabOffset = symtab.Offset
		strtabOffset = strtab.Offset

		symtabSize = int(symtab.Size)
		strtabSize = int(strtab.Size)
	}

	copy((*data)[symtabOffset:], utils.GenerateGibberish(symtabSize)) // SHT_SYMTAB
	copy((*data)[strtabOffset:], utils.GenerateGibberish(strtabSize)) // SHT_STRTAB

	// METHOD 3
	// Prevents bninja and IDA successfully from opening the binary
	// Modify EI_CLASS, EI_DATA, EI_VERSION, EI_PAD
	copy((*data)[elf.EI_CLASS:], utils.GenerateGibberish(1))
	copy((*data)[elf.EI_DATA:], utils.GenerateGibberish(1))
	copy((*data)[elf.EI_VERSION:], utils.GenerateGibberish(1))
	copy((*data)[elf.EI_OSABI:], utils.GenerateGibberish(1))
	copy((*data)[elf.EI_ABIVERSION:], utils.GenerateGibberish(1))
	copy((*data)[elf.EI_PAD:], utils.GenerateGibberish(7))
	copy((*data)[20:], utils.GenerateGibberish(1)) // E_VERSION

	fmt.Println("[+] Locking successful")
}