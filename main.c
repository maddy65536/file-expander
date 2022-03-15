#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

#include "expand.h"

typedef enum mode { None, Expand, Unexpand } mode;

int main(int argc, char *argv[]) {
    // configuration variables to be set below
    mode expandMode = None;
    char *inputPath = NULL;
    char *outputPath = NULL;

    // store result from getopt
    int opt;
    while ((opt = getopt(argc, argv, "i:o:euh")) != -1) {
        switch (opt) {
            case 'i':
                inputPath = optarg;
                break;
            case 'o':
                outputPath = optarg;
                break;
            case 'e':
                expandMode = Expand;
                break;
            case 'u':
                expandMode = Unexpand;
                break;
            case '?':
                return 1;
                break;
            case 'h':
            default:
                printf("usage:\n");
                printf("\texpand a file:   file-expander -e -i <input-filename> -o <output-filename>\n");
                printf("\tunexpand a file: file-expander -u -i <input-filename> -o <output-filename>\n");
                return 0;
        }
    }

    // ensure arguments are valid
    if (expandMode == None) {
        fprintf(stderr, "error: must set a mode\n");
        return 1;
    }

    if (inputPath == NULL) {
        fprintf(stderr, "error: must supply an input file\n");
        return 1;
    }

    if (outputPath == NULL) {
        fprintf(stderr, "error: must supply an output file\n");
        return 1;
    }

    // run the expansion/unexpansion
    if (expandMode == Expand) {
        int res = expandFile(inputPath, outputPath);
        if (res != 0) {
            return 1;
        }
    } else {
        int res = unexpandFile(inputPath, outputPath);
        if (res != 0) {
            return 1;
        }
    }


    return 0;
}
