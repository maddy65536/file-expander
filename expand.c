#include <stdio.h>

// requires an 8 byte buffer
void expandChar(char input, char *outputBuf) {
    for (int i = 0; i < 8; i++) {
        if ((input >> (7 - i)) & 1) {
            outputBuf[i] = '1';
        } else {
            outputBuf[i] = '0';
        }
    }
}

// assumes that input is correctly formatted (8 byte char array, only 0 and 1)
char unexpandChar(char *input) {
    char res = 0;
    for (int i = 0; i < 8; i++) {
        res <<= 1;
        if (input[i] == '1') {
            res |= 1;
        }
    }
    return res;
}

// checks if a string is all 0 and 1, assumes length 8
int checkFormat(char* input) {
    for (int i = 0; i < 8; i++) {
        if (input[i] != '0' && input[i] != '1') {
            return 0;
        }
    }
    return 1;
}

int expandFile(char *input, char *output) {
    // debug
    printf("expanding:\ninput: %s\noutput: %s\n", input, output);
    
    // open input file and ensure it was opened, return 1 to indicate an error
    FILE *inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("failed to open input file: %s\n", input);
        return 1;
    }

    // open output file and ensure it was opened, return 1 to indicate an error
    FILE *outputFile = fopen(output, "wb");
    if (outputFile == NULL) {
        // close input file since we're aborting
        fclose(inputFile);
        printf("failed to open output file: %s\n", output);
        return 1;
    }
    
    // buffers to hold character read from file and its expanded version
    char readChar;
    char expanded[8];
    // read each byte from the input file, expand it, and write to output file
    while (fread(&readChar, 1, 1, inputFile)) {
        expandChar(readChar, expanded);
        fwrite(expanded, 1, 8, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

int unexpandFile(char *input, char *output) {
    // debug
    printf("unexpanding:\ninput: %s\noutput: %s\n", input, output);

    // open input file and ensure it was opened, return 1 to indicate an error
    FILE *inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("failed to open input file: %s\n", input);
        return 1;
    }

    // open output file and ensure it was opened, return 1 to indicate an error
    FILE *outputFile = fopen(output, "wb");
    if (outputFile == NULL) {
        // close input file since we're aborting
        fclose(inputFile);
        printf("failed to open output file: %s\n", output);
        return 1;
    }
    
    char expanded[8]; 
    size_t numRead;
    while((numRead = fread(&expanded, 1, 8, inputFile))) {
        if (numRead < 8 || !checkFormat(expanded)) {
            printf("incorrect file format, aborting");
            return 1;
        }
        char res = unexpandChar(expanded);
        fwrite(&res, 1, 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
