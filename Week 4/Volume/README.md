CS50 Week 4 — Volume
Description

This program modifies the volume of a WAV audio file by a given scaling factor.

The program reads the WAV file header, copies it to the output file, then reads each audio sample, scales its value, and writes the modified sample to the output file.

Concepts Learned
File I/O
fopen() and fclose()
fread() and fwrite()
Buffers
int16_t
uint8_t
Command-line arguments
WAV file structure
Audio samples
How It Works

The program accepts three command-line arguments:

./volume input.wav output.wav factor

For example:

./volume input.wav output.wav 2.0

A factor of 2.0 doubles the volume, while 0.5 reduces the volume by half.

File
volume.c — Source code for the volume modification program.
Course

Harvard CS50x — Week 4: Memory

Author

Mubeen Khan
