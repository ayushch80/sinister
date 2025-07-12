# sinister 💀  
### Advanced (Simple) Binary Obfuscation Toolkit

**Sinister** is an ELF binary obfuscator built to weaponize your executables against reverse engineering. It applies low-level transformations to make binaries harder to analyze, decompile, or understand.

---

## ⚙️ Features

### ✅ **Completed**  
- Nothing yet... but soon! 💀 

### 🔥 **In Active Development**
- [x] **Symbol Renaming** *(Initial Support)*  
  🔹 Currently supports renaming of:  
  &nbsp;&nbsp;&nbsp;&nbsp;• **Nearly all `STB_LOCAL` and `STB_GLOBAL` symbols**
  ✔️ Renames safely within `.symtab` and `.strtab`  
  ❌ Does *not yet* handle `.dynsym`, relocations, or dynamic resolution (`dlsym`, plugins)


### 🚀 **Upcoming**
- [ ] **Dynamic Buffer Allocation**  
- [ ] **Flow Flattening**  
- [ ] **Code Injection**  
- [ ] **String Obfuscation**  
- [ ] **Anti-Debugging**

---

## 🚀 Quickstart

### 📥 Clone the Repo
```bash
git clone https://github.com/ayushch80/sinister.git
cd sinister
````

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

## 💡 Example Usage (WIP)

```bash
# Rename all safe local symbols
./sinister -inp ./binary -out ./binary_out -rename
```

---

## 📂 Project Structure

| Path                | Description                                                      |
|---------------------|------------------------------------------------------------------|
| `renaming/`         | Core logic for symbol renaming and symbol table manipulation     |
| `utils/`            | Helper functions for logging, ELF utilities, and common routines |
| `main.go`           | Entry point for CLI — parses arguments and dispatches commands   |
| `go.mod` / `go.sum` | Go module definition and dependency tracking                     |

---

## ⚖️ License

Sinister is licensed under the [Apache License 2.0](LICENSE)

---

> 🛑 **Disclaimer:** This tool is for educational and research use only. Do not use it on software you don't own or audit with permission.