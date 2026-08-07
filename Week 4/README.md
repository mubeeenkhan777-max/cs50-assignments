# CS50 Week 4 - Memory

## Overview

Week 4 of Harvard's CS50x introduces memory, file I/O, pointers, and working with data at a lower level.

Through these assignments, I learned how computers represent and manipulate data in memory and files, including audio files, images, and deleted data.

## Assignments

### 1. Volume

Modified the volume of a WAV audio file by reading its samples and multiplying each sample by a given scaling factor.

**Concepts Learned**
- File I/O
- `fopen()` / `fclose()`
- `fread()` / `fwrite()`
- Buffers
- `int16_t`
- Command-line arguments

### 2. Filter - Less

Implemented image filters for BMP images.

The filters include:
- Grayscale
- Sepia
- Reflection
- Blur

**Concepts Learned**
- Structs
- Two-dimensional arrays
- Pixels
- RGB values
- Image processing
- Nested loops

### 3. Recover

Recovered deleted JPEG images from a forensic image of a memory card.

The program searches 512-byte blocks for JPEG signatures and reconstructs the images into separate JPEG files.

**Concepts Learned**
- File I/O
- Buffers
- JPEG signatures
- `uint8_t`
- Bitwise operations
- `sprintf()`
- Data recovery

## Skills Developed

- C Programming
- File Handling
- Memory Management
- Binary Data Processing
- Image Processing
- Audio Processing
- Problem Solving
- Debugging

## Technologies Used

- C
- CS50 Library
- VS Code
- Git
- GitHub

## Repository Structure

```text
Week4/
├── volume/
│   ├── volume.c
│   └── README.md
│
├── filter-less/
│   ├── helpers.c
│   └── README.md
│
└── recover/
    ├── recover.c
    └── README.md
