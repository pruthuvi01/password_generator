#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char randomCharacter(const char *charSet) {
    int index = rand() % strlen(charSet);
    return charSet[index];
}

// Helper function to shuffle an array of characters randomly
void shuffle(char *array, int n) {
    if (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            char temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
}

char *GenerateCharSet(char *string, int length, const char *charSet) {
    int charSetLength = strlen(charSet);

    // Create a temporary character array for shuffling
    char tempCharSet[charSetLength + 1];
    strcpy(tempCharSet, charSet);

    // Shuffle the characters randomly
    shuffle(tempCharSet, charSetLength);

    // Generate the password with the shuffled characters
    for (int i = 0; i < length; ++i) {
        string[i] = tempCharSet[i % charSetLength];
    }
    string[length] = '\0';
    return string + length;
}

void printUsage() {
    printf("Usage: password generator [options]\n");
    printf("Options:\n");
    printf("  -l <length>           Specify the password length\n");
    printf("  -u <num_upper>        Number of uppercase characters\n");
    printf("  -w <num_lower>        Number of lowercase characters\n");
    printf("  -s <num_special>      Number of special characters\n");
    printf("  -n <num_digits>       Number of numeric digits\n");
    printf("  -c <num_combinations> Number of different combinations\n");
}

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        printf("You can make different combinations specifying how many characters and character types should be in your password.\n\n");
        printUsage();
        printf("\nExample case : './pwd -l 10 -u 3 -w 3 -s 2 -n 2 -c 3'\nThis will generate 3 different combinations with a total of 10 characters including 3 uppercase, 3 lowercases, 2 special characters, and 2 digits\n");
        exit(EXIT_FAILURE);
    }

    const char *lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
    const char *uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *digitChars = "0123456789";
    const char *specialChars = "!@#%^&*()_+=";

    int passwordLength = 0;
    int NumOfUpper = 0;
    int NumOfLower = 0;
    int NumOfSpecial = 0;
    int NumOfNum = 0;
    int NumOfPwd = 1; // Default value for the number of different combinations

    int opt;
    while ((opt = getopt(argc, argv, "l:u:w:s:n:c:")) != -1) {
        switch (opt) {
        case 'l':
            passwordLength = atoi(optarg);
            break;
        case 'u':
            NumOfUpper = atoi(optarg);
            break;
        case 'w':
            NumOfLower = atoi(optarg);
            break;
        case 's':
            NumOfSpecial = atoi(optarg);
            break;
        case 'n':
            NumOfNum = atoi(optarg);
            break;
        case 'c':
            NumOfPwd = atoi(optarg);
            break;
        default:
            printUsage();
            exit(EXIT_FAILURE);
        }
    }

    // Check if all required options are provided
    if (passwordLength <= 0 || NumOfUpper < 0 || NumOfLower < 0 || NumOfSpecial < 0 || NumOfNum < 0) {
        printf("Error: Invalid arguments.\n");
        printUsage();
        exit(EXIT_FAILURE);
    }
    if (NumOfUpper + NumOfLower + NumOfSpecial + NumOfNum != passwordLength) {
        printf("Error: Password length does not match with the provided number of characters.\n");
        printUsage();
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < NumOfPwd; i++) {
        char password[100] = "";
        int totalChars = NumOfUpper + NumOfLower + NumOfSpecial + NumOfNum + 1; // +1 for '\0'
        char charSet[totalChars];

        // Separate character sets for different types of characters
        char uppercaseSet[NumOfUpper + 1];
        char lowercaseSet[NumOfLower + 1];
        char specialSet[NumOfSpecial + 1];
        char digitSet[NumOfNum + 1];

        // Generate separate character sets for each type of character
        GenerateCharSet(uppercaseSet, NumOfUpper, uppercaseChars);
        GenerateCharSet(lowercaseSet, NumOfLower, lowercaseChars);
        GenerateCharSet(specialSet, NumOfSpecial, specialChars);
        GenerateCharSet(digitSet, NumOfNum, digitChars);

        // Concatenate the character sets to form the main charSet
        strcpy(charSet, uppercaseSet);
        strcat(charSet, lowercaseSet);
        strcat(charSet, specialSet);
        strcat(charSet, digitSet);

        // Generate the password
        GenerateCharSet(password, passwordLength, charSet);

        // Print the generated password
        printf("Generated Password [%d]: %s\n", i + 1, password);
    }

    return 0;
}
