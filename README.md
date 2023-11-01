# Forever Virtual Inputter

Forever Virtual Inputter (FVI) is a command-line tool that allows you to simulate virtual input on your computer. It enables you to automate repetitive tasks by sending keystrokes or mouse movements. With FVI, you can create scripts to mimic user input and execute them repeatedly.


## Requirements

FVI requires the following dependencies:

- [gcc] (any version might be capable)

## Build

To Build FVI, follow these steps:

1. Clone the repository or download the source code.
2. Navigate to the directory where the source code is located.
3. Run the command:

```
gcc .\getfile.c .\outchar.c .\getopt.c .\forever-virtual-inputter.c -o forever-virtual-inputter -static-libgcc -lgdi32 -lcomdlg32 -O2
```

This will compile and install FVI on your system.


## Usage

To use FVI, open a terminal or command prompt and run the following command:

```
fvi [<switches>...] <archive_name>/<off_time>
```

### Switches

- `-h`: Show the usage message.
- `-f`: Specify a text file containing the input script.
- `-t`: Specify the off time (in seconds). The default off time is 25 ms.
- `-v`: Check the version of FVI.

### Examples

1. Execute directly
```
fvi
```

2. Execute an input script from a text file named `test.txt`:
```
fvi -f test.txt
```

3. Execute an input script from a text file named `test.txt`, with an off time of 50 seconds:
```
fvi -t 50 -f test.txt
```
