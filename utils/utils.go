package utils

import (
	"encoding/binary"
	"math/rand"
	"time"
)

func GenerateGibberish(size int) []byte {
	rand.Seed(time.Now().UnixNano())
	const charset = "abcdefghijklmnopqrstuvwxyz" +
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ" +
		"0123456789"  +
		   "!@#$%^&*()-_=+[]{}|;:,.<>?/\\"

	result := make([]byte, size)
	for i := range result {
		result[i] = charset[rand.Intn(len(charset))]
	}
	return result
}

func BytesToUint64LE(b []byte) uint64 {
	if len(b) < 8 {
		panic("input must be at least 8 bytes")
	}
	return binary.LittleEndian.Uint64(b)
}

func BytesToUint32LE(b []byte) uint32 {
	if len(b) < 4 {
		panic("input must be at least 4 bytes")
	}
	return binary.LittleEndian.Uint32(b)
}

func BytesToUint16LE(b []byte) uint16 {
	if len(b) < 2 {
		panic("input must be at least 2 bytes")
	}
	return binary.LittleEndian.Uint16(b)
}

func BytesToUint8LE(b []byte) uint8 {
	if len(b) < 1 {
		panic("input must be at least 1 byte")
	}
	return uint8(b[0])
}
