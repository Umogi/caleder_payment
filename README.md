# Dues Manager

This is a simple command-line program in C for managing financial dues. It allows users to add, remove, view, and save their dues. The program also automatically updates dues by adding $2 per month for unpaid amounts.

## Features
- Add new dues with a name and amount.
- Remove existing dues.
- View all recorded dues.
- Save and load dues from a file (`save.txt`).
- Automatically increases dues if they are unpaid for months past the 21st.

## Technologies Used
- C
- File I/O for saving and loading data.
- Time functions for due date calculations.

## Installation & Usage
1. Compile the program using GCC:
   ```sh
   gcc -o dues_manager dues_manager.c
   ```
2. Run the executable:
   ```sh
   ./dues_manager
   ```
3. Follow the menu prompts to manage dues.
4. The program automatically saves dues when exiting.
