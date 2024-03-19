Aysha Altinsoy (ata89) and Hala Belgaid (hcb42)

README for Spell Checker Project

Overview
This spell checker, `spchk`, validates the spelling in text files. It traverses directories and files, checks words against a sorted dictionary using binary search, and reports incorrect spellings or capitalization.

Requirements
- C compiler (e.g., GCC)
- Standard C library

Compilation
Compile with `gcc -o spchk spchk.c`.

Usage
Run `./spchk <file_or_directory> ...` to check one or more files or directories. The program recursively processes text files, printing each incorrect word with its location.

Implementation Details
- `process_file` reads text files, identifying words.
- `process_directory` traverses directories recursively.
- `binary_search` checks word existence in the dictionary.
- `checkWord` validates spelling and capitalization.
- Case sensitivity and correct capitalization are enforced.

Test Cases

For a file containing misspelled words, ensure each misspelling is reported with the correct line and column number.
For a directory test, ensure all text files are processed and misspellings in each file are correctly reported.
Case sensitivity tests should confirm that the spell checker distinguishes between case variations of words in the dictionary.

Test Scenarios

Single File Check: Run spell checker on a single text file.
Directory Check: Run spell checker on a directory containing multiple text files.
Case Sensitivity Test: Verify that the spell checker correctly identifies case-sensitive misspellings.
Capitalization Test: Test the spell checker's ability to identify incorrect capitalization.

Ensure the dictionary is pre-sorted and loaded into memory before execution. Adjust `MAX_WORD_LEN` and `MAX_LINE_LEN` as needed for larger texts or words.