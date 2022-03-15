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

int expandFile(char *input, char *output) {
    printf("expanding:\ninput: %s\noutput: %s\n", input, output);
    
    char expanded[8];
    expandChar(input[0], expanded);
    printf("expanded: %s\n", expanded);
    return 0;
}

int unexpandFile(char *input, char *output) {
    printf("unexpanding:\ninput: %s\noutput: %s\n", input, output);

    printf("unexpanded: %c\n", unexpandChar(input));
    return 0;
}
