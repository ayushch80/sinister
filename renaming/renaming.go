package renaming

import (
	"debug/elf"
	"fmt"
	"log"
	"sinister/utils"
)

func BytesToSymtab(b []byte) SymbolTable {
	symtab := SymbolTable{
		Symbols: []Symbol{},
	}

	if len(b)%24 != 0 {
		log.Fatalf("[-] Failed while parsing Symbol Table")
	}

	for i := 0; i < len(b); i += 24 {
		sym := Symbol{
			st_name:  utils.BytesToUint32LE(b[i : i+4]),
			st_info:  utils.BytesToUint8LE(b[i+4 : i+5]),
			st_other: utils.BytesToUint8LE(b[i+5 : i+6]),
			st_shndx: utils.BytesToUint16LE(b[i+6 : i+8]),
			st_value: utils.BytesToUint64LE(b[i+8 : i+16]),
			st_size:  utils.BytesToUint64LE(b[i+16 : i+24]),
		}
		symtab.Symbols = append(symtab.Symbols, sym)
	}

	return symtab
}

func RenameSymbols(filepath string, data *[]byte) {
	// Read the file
	fmt.Println("[+] Reading the file")
	ELF, err := elf.Open(filepath)
	if err != nil {
		log.Fatalf("[-] Failed while reading ELF file at : %s\n", filepath)
	}

	// Check ELF for 64-bit format
	if ELF.FileHeader.Class != elf.ELFCLASS64 {
		log.Fatalf("[-] Currently only 64-bit binaries are supported.")
	}

	// Find `.symtab` and `.strtab` sections
	var symtabData, strtabData []byte
	var strtabOffset uint64
	{
		symtab := ELF.Section(".symtab")
		if symtab == nil {
			log.Fatalf("[-] Unable to locate '.symtab'\n")
		}

		strtab := ELF.Section(".strtab")
		if symtab == nil {
			log.Fatalf("[-] Unable to locate '.strtab'\n")
		}

		symtabData, err = symtab.Data()
		if err != nil {
			log.Fatalf("[-] Failed while reading '.symtab'")
		}
		strtabData, err = strtab.Data()
		if err != nil {
			log.Fatalf("[-] Failed while reading '.strtab'")
		}
		strtabOffset = strtab.Offset
	}

	symtab := BytesToSymtab(symtabData)

	// Save STB_LOCAL - STT_GNU_IFUNC symbols in an array
	var goodSymbols []Symbol
	for _, sym := range symtab.Symbols {
		st_bind := elf.ST_BIND(sym.st_info)
		st_type := elf.ST_TYPE(sym.st_info)

		// Checks
		if st_bind == elf.STB_LOCAL && st_type != elf.STT_GNU_IFUNC {
			goodSymbols = append(goodSymbols, sym)
		}
	}

	// Rename the symbols to gibberish text
	count := 0
	for _, sym := range goodSymbols {
		var name []byte
		for i := sym.st_name; strtabData[i] != 0; i++ {
			name = append(name, strtabData[i])
		}

		newName := utils.GenerateGibberish(len(name))
		copy(strtabData[sym.st_name:], newName)

		count++
		fmt.Printf("[*] Renaming %s to %s\n", string(name), string(newName))
	}

	fmt.Printf("[+] Successfully renamed %d/%d symbols.\n", count, len(symtab.Symbols))

	// Write the new strtab to the data
	copy((*data)[strtabOffset:], strtabData)
}
