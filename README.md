# sinister 💀

### Advanced (Simple) Binary Obfuscation Toolkit

**Sinister** is an ELF binary obfuscator built to weaponize your executables against reverse engineering. It applies low-level transformations to make binaries harder to analyze, decompile, or understand — all while remaining executable.

---

## ⚙️ Features

### ✅ **Completed**

* Nothing yet... but soon! 💀

### 🔥 **In Active Development**

* [x] **Symbol Renaming** *(Initial Support)*  
  🔹 Supports renaming of:  
      • **All `STB_LOCAL` and `STB_GLOBAL` symbols**, except `STT_GNU_IFUNC`  
  ✔️ Renames safely within `.symtab` and `.strtab`  
  ❌ Does *not yet* handle `.dynsym`, relocations, or dynamic resolution (`dlsym`, plugins)

* [x] **ELF Locking** *(Experimental)*  
  🔹 Corrupts ELF internals to break analysis by tools like IDA, Ghidra, radare2, Binary Ninja  
  ✔️ Techniques include:  
      • `.symtab`/`.strtab` poisoning  
      • ELF header sabotage (`EI_CLASS`, `EI_VERSION`, etc.)

---

## 🚀 Upcoming

* [ ] **Anti-Debugging**
* [ ] **Code Injection**
* [ ] **Dynamic Buffer Allocation**
* [ ] **Flow Flattening**
* [ ] **Packing**
* [ ] **String Obfuscation**

---

## 🚀 Quickstart

### 📥 Clone the Repo

```bash
git clone https://github.com/ayushch80/sinister.git
cd sinister
```

### 📦 Install Dependencies

#### 🦫 Golang (Required)

Make sure Go is installed (version ≥ 1.19 recommended):

```bash
go version
```

If not installed:

```bash
sudo apt install golang
```

---

### 🛠️ Build

```bash
go build .
```

---

### 🧪 Run

```bash
./sinister
```

---

## 💡 Example Usage

```bash
# Rename all safe local symbols
./sinister -inp ./binary -out ./binary_out -rename

# Lock binary to break RE tools
./sinister -inp ./binary -out ./binary_out -lock
```

---

## 📂 Project Structure

| Path                | Description                                                      |
| ------------------- | ---------------------------------------------------------------- |
| `renaming/`         | Core logic for symbol renaming and symbol table manipulation     |
| `locking/`          | ELF locking routines to sabotage reverse engineering tools       |
| `utils/`            | Helper functions for logging, ELF utilities, and common routines |
| `main.go`           | Entry point for CLI — parses arguments and dispatches commands   |
| `go.mod` / `go.sum` | Go module definition and dependency tracking                     |

---

## ⚖️ License

Sinister is licensed under the [Apache License 2.0](LICENSE)

---

> 🛑 **Disclaimer:** This tool is for educational and research purposes only. Do not use it on software you don’t own or without explicit permission.

---

Let me know if you want a cool badge, example binaries, or to automatically detect if locking was successful (via broken `readelf`).
