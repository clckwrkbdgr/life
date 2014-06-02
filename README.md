# Life

Conway's Game of Life console implementation. Uses `ncurses` to display field and cells.

## Installation

Depends on `ncursesw` library.
Just run `make` and run produced `life` file.

## Usage

Runs only on terminal with Unicode and colour support, as it uses some Unicode symbols.

Usage:

	life --help
	life PATTERN_NAME
	life FILE_NAME

`PATTERN_NAME` is a name from the list below. If no such pattern exists, it is treated as a file name.
Pattern in file should use spaces (0x20) for empty cells and any non-space for living ones.
Size of field is determined using the line with the max width and a total count of the lines.

Predifined patterns list:

* **glider** - Common glider
* **gun** - Glider gun
* **r-pentomino** - R-pentomino Methuselah
* **diehard** - Diehard Methuselah
* **acorn** - Acorn Methuselah
* **infinite1** - Infinite pattern
* **infinite2** - Infinite pattern
* **infinite3** - Infinite pattern
