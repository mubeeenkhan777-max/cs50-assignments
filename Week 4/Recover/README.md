# CS50 Week 4 - Recover

## Description

This program recovers deleted JPEG images from a forensic image of a memory card.

The program reads the memory card in 512-byte blocks, identifies JPEG file signatures, and reconstructs each JPEG into a separate image file.

## Concepts Learned

- File I/O
- `fopen()` and `fclose()`
- `fread()` and `fwrite()`
- Buffers
- `uint8_t`
- JPEG file signatures
- Command-line arguments
- `sprintf()`
- Bitwise operations
- Memory card data recovery

## Files

- `recover.c` — Source code for the JPEG recovery program.

## Course

Harvard CS50x — Week 4: Memory

## Author

Mubeen Khan
