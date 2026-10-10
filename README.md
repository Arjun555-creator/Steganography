# Steganography

## Project Overview

Steganography is a C-based application that hides secret text messages inside BMP images using the Least Significant Bit (LSB) technique.

The application encodes a secret message into a source image to generate a stego image. It also supports decoding the stego image to recover the hidden message.

This project demonstrates how data can be embedded and retrieved from image files using bitwise operations and file handling in C.

## Features

- Encode secret text into a BMP image
- Decode hidden messages from stego images
- Use LSB encoding to embed secret data
- Generate a new image containing the hidden message
- Recover the original secret message
- Support custom output filenames
- Validate input files and encoding operations
- Handle unsupported operations

## Technologies Used

- C
- GCC
- Linux
- BMP Image Format
- File Handling
- Bitwise Operations

## Concepts Used

- Pointers
- Structures
- Functions
- Bitwise Operators
- File Handling
- Binary File Processing
- Command-Line Arguments
- Modular Programming
- Error Handling
- Least Significant Bit (LSB) Encoding

## Compilation

Compile the project using GCC:

```bash
gcc *.c -o lsb_steg
```

## Usage

Encode a secret message into a BMP image:

```bash
./lsb_steg -e beautiful.bmp secret.txt
```

Specify a custom output image:

```bash
./lsb_steg -e beautiful.bmp secret.txt my_stego.bmp
```

Decode the hidden message:

```bash
./lsb_steg -d my_stego.bmp recovered.txt
```

Display the supported command format:

```bash
./lsb_steg -h
```

## Project Objective

The objective of this project is to implement image-based data hiding and recovery using LSB encoding while applying bitwise operations, binary file handling, and modular C programming.

## Author

Arjun
