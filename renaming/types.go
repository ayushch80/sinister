package renaming

type Symbol struct {
	st_name  uint32
	st_info  uint8
	st_other uint8
	st_shndx uint16
	st_value uint64
	st_size  uint64
}

type SymbolTable struct {
	Symbols []Symbol
}
