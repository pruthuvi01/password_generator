# Password Generator

The Password Generator is a command-line utility written in C that allows you to generate random passwords with different combinations of characters, including uppercase letters, lowercase letters, special characters, and digits. The utility provides various options to customize the generated passwords based on your requirements.

## Features

- Generate random passwords with specified lengths and character combinations.
- Customize the number of uppercase letters, lowercase letters, special characters, and digits in the passwords.
- Option to generate multiple different combinations of passwords.

## Usage

To run the password generator, you can use the following command-line arguments:

./pwd -l <length> -u <num_upper> -w <num_lower> -s <num_special> -n <num_digits> -c <num_combinations>


- `-l <length>`: Specify the total length of the generated password.
- `-u <num_upper>`: Specify the number of uppercase characters in the password.
- `-w <num_lower>`: Specify the number of lowercase characters in the password.
- `-s <num_special>`: Specify the number of special characters in the password.
- `-n <num_digits>`: Specify the number of numeric digits in the password.
- `-c <num_combinations>`: Specify the number of different combinations of passwords to generate (optional, default is 1).

## Examples

1. Generate a password with 10 characters, including 3 uppercase, 3 lowercase, 2 special characters, and 2 digits:

./pwd -l 10 -u 3 -w 3 -s 2 -n 2


2. Generate 3 different combinations of passwords, each with a total of 8 characters, including 2 uppercase, 2 lowercase, 2 special characters, and 2 digits:

./pwd -l 8 -u 2 -w 2 -s 2 -n 2 -c 3


## Building the Project

To build the Password Generator, make sure you have a C compiler (e.g., GCC) installed on your system. Then, use the following command:

gcc -o pwd password_generator.c

