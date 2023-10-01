# Minishell

## Description

Minishell is a simplified UNIX shell implemented in C. It supports basic shell functionalities like `cd`, `export`, wildcard expansion, and more.

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Structure](#structure)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Features

- Built-in commands: `cd`, `export`, `env`, etc.
- Environment variable expansion
- Wildcard expansion
- Error handling
- Command execution
- Signal handling

## Installation

### Requirements
- GCC 9.0+
- readline 8.2
- Linux/MacOS or Windows Subsystem for Linux

### Build and Compile
```bash
git clone git@github.com:emartinez-dev/minishell.git
cd Minishell
make
```

## Usage

Run the shell with:

```bash
./minishell
```

## Structure

### Directories and Files

- `include/`: Header files.
- `src/`: Source files.
  - `builtins/`: Built-in shell commands.
  - `executor/`: Command execution logic.
  - `expander/`: String expansion logic.
  - `parser/`: Shell parsing logic.
  - `prompt/`: Prompt display logic.
  - `signals/`: Signal handling.
  - `utils/`: Utility functions.
  - `wildcard/`: Wildcard expansion logic.

### Makefile

Run `make` to compile the Minishell executable.
Additional Makefile targets:
- `clean`: Removes all compiled object files.
- `fclean`: Removes both compiled object files and the executable.
- `re`: Runs `fclean` and compiles the project again.

## Contributing

1. Fork the project.
2. Create your feature branch: `git checkout -b feature/fooBar`
3. Commit your changes: `git commit -am 'Add fooBar'`
4. Push to the branch: `git push origin feature/fooBar`
5. Open a pull request.

## License

This project is licensed under The Unlicense - see the [LICENSE.md](LICENSE.md) file for details.

## Contact

Created by [Enrique Martínez](https://github.com/emartinez-dev/) and [Juan A. García](https://github.com/Juan-aga) - feel free to contact us!
