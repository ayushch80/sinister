package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"sinister/renaming"
	"sinister/locking"
)

func main() {
	fmt.Println("sinister v0.1")

	// Define CLI flags
	inpath := flag.String("in", "", "Path to input binary file")
	outpath := flag.String("out", "", "Path to save renamed output file")
	rename := flag.Bool("rename", false, "Enable symbol renaming")
	lock := flag.Bool("lock", false, "Enable ELF locking")
	flag.Parse()

	if *inpath == "" || *outpath == "" {
		fmt.Println("Usage: sinister -in <input_file> -out <output_file> [-rename|-lock]")
		flag.PrintDefaults()
		os.Exit(1)
	}

	fmt.Println("[*] Input :", *inpath)

	// Read the file
	inpData, err := os.ReadFile(*inpath)
	if err != nil {
		log.Fatalf("[-] Failed while reading file at: %s\nError: %v\n", *inpath, err)
	}

	// Do symbol renaming
	if *rename {
		fmt.Println("[+] Renaming symbols...")
		renaming.RenameSymbols(*inpath, &inpData)
	}

	// Do ELF locking
	if *lock {
		fmt.Println("[+] Locking ELF...")
		locking.LockBinary(*inpath, &inpData)
	}

	// Write modified binary with executable permissions
	err = os.WriteFile(*outpath, inpData, 0755)
	if err != nil {
		log.Fatalf("[-] Failed while writing file at: %s\nError: %v\n", *outpath, err)
	}

	fmt.Println("[+] Saved file at:", *outpath)
}
