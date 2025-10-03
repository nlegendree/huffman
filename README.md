# Huffman Compression Algorithm

A file compression and decompression tool implementing the Huffman coding algorithm in C. This project demonstrates efficient data structures (priority queues, binary trees) and bitwise operations for lossless compression.

## Features

- **Lossless compression** using Huffman coding algorithm
- **Custom data structures**: Priority queues, binary trees, encoding tables
- **Binary file handling** with custom `.huff` format
- **Comprehensive test suite** using CUnit
- **Memory-safe** implementation with proper cleanup

## Quick Start

### Building

```bash
make release          # Build optimized version
make debug            # Build with debug symbols
make tests            # Build and run all tests
```

### Usage

```bash
# Compress a file
./bin/huffman c myfile.txt
# Creates myfile.txt.huff

# Decompress a file
./bin/huffman d myfile.txt.huff
# Restores myfile.txt
```

## Project Structure

```
├── src/              # Implementation files
├── include/          # Header files
├── bin/              # Compiled executable (generated)
└── obj/              # Object files (generated)
```

### Core Components

The implementation uses Abstract Data Types (TADs):

- **Octet**: 8-bit byte wrapper
- **Bit**: Binary bit representation
- **CodeBinaire**: Variable-length binary codes (up to 255 bits)
- **Statistiques**: Byte frequency counter (256 slots)
- **ArbreDeHuffman**: Huffman tree with weighted nodes
- **FileDePriorite**: Priority queue for tree construction
- **TableDeCodage**: Byte-to-code mapping table

## Algorithm Overview

### Compression Pipeline

1. **Calculate statistics**: Count byte occurrences in input file
2. **Build Huffman tree**: Use priority queue to construct optimal tree
3. **Generate coding table**: Traverse tree to assign binary codes
4. **Encode file**: Write header (magic number + statistics) + encoded data

### Decompression Pipeline

1. **Validate format**: Check magic number (`0x0B1213D2`)
2. **Read statistics**: Extract byte frequencies from header
3. **Rebuild tree**: Reconstruct identical Huffman tree
4. **Decode file**: Traverse tree bit-by-bit to restore original bytes

## File Format

Compressed `.huff` files contain:
- Magic number (4 bytes): `0x0B1213D2`
- Total byte count (8 bytes)
- Occurrence array (256 × 8 bytes)
- Encoded bit stream

## Testing

Run individual test suites:

```bash
make tests                    # Run all tests
./tests/testArbre            # Test Huffman tree
./tests/testCodeBinaire      # Test binary codes
./tests/testFile             # Test priority queue
./tests/testTable            # Test encoding table
```

## Documentation

Generate Doxygen documentation:

```bash
make doc                     # Creates doc/html/index.html
```

## Contributors

This project was developed as a team assignment at INSA Rouen Normandie (2023-2024) by a group of 5 students.

*Note: This repository was migrated from our school's GitLab instance. Full commit history has been preserved to maintain transparency of contributions.*

## Technical Details

- **Language**: C (C99 standard)
- **Compiler**: GCC with `-Wall -pedantic`
- **Testing**: CUnit framework
- **Memory management**: Manual allocation/deallocation with proper cleanup
- **Error handling**: errno-based error reporting

## License

Academic project - INSA Rouen Normandie

---

*Developed as part of the Algorithms course (ITI 3rd year)*
