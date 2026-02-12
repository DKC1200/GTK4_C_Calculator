# GTK Calculator

A lightweight, modern calculator application built with GTK4 and C.

![Calculator Screenshot](screenshot.png)
<img width="352" height="499" alt="Calculator" src="https://github.com/user-attachments/assets/513b561c-4f9b-4c3e-b42d-3a86671120cb" />

## Features

- ✨ Clean, intuitive interface
- ➕ Basic arithmetic operations (+, -, *, /)
- ⌨️ Keyboard support (press Enter to calculate)
- 🐧 Native Linux application with GTK4
- 📦 Available as Flatpak

## Installation

### Linux (Flatpak - Recommended)
```bash
# Install the Flatpak bundle
flatpak install calculator.flatpak

# Run the application
flatpak run com.debora.Calculator
```

### Windows (MSYS2)

1. Install [MSYS2](https://www.msys2.org/)
2. Open MSYS2 MinGW 64-bit terminal
3. Install dependencies:
```bash
pacman -S mingw-w64-x86_64-gtk4 mingw-w64-x86_64-gcc mingw-w64-x86_64-meson mingw-w64-x86_64-ninja
```
4. Build:
```bash
meson setup build
meson compile -C build
./build/calculator.exe
```

## Usage

### Mouse
- Click buttons to enter numbers and operators
- Click `=` to calculate result
- Click `C` to delete last character

### Keyboard
- Type numbers and operators directly
- Press `Enter` to calculate
- Press `Backspace` to delete last character

## Project Structure
```
gtk-calculator/
├── calculator.h           # Header file with declarations
├── main.c                 # Application entry point
├── calculator_gui.c       # GUI implementation
├── calculator_logic.c     # Calculator logic and math operations
├── meson.build           # Build configuration
└── com.debora.Calculator.yml  # Flatpak manifest
```

## Technical Details

- **Language**: C
- **GUI Framework**: GTK4
- **Build System**: Meson
- **Architecture**: Modular design separating GUI and logic
- **Calculator Logic**: Shunting-yard algorithm for expression evaluation

## Algorithm

The calculator uses a stack-based algorithm to evaluate expressions with proper operator precedence:
- Multiplication and division have higher precedence than addition and subtraction
- Operations are evaluated left-to-right for operators of equal precedence

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Future updates:
- [ ] Add more operations (power, square root, etc.)
- [ ] History feature
- [ ] Keyboard shortcuts
- [ ] Themes/dark mode
- [ ] Scientific calculator mode
- [ ] Windows installer

### Build directories
build/
build-dir/
repo/

### Meson files
.ninja_deps
.ninja_log

### Compiled files
*.o
*.exe
calculator

### Flatpak
*.flatpak

# IDE files
.vscode/
.idea/
*.swp
*~
