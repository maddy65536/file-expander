#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum mode { None, Expand, Compress } mode;

int main(int argc, char *argv[]) {
    // configuration variables to be set below
    mode expandMode = None;
    char *inputPath = NULL;
    char *outputPath = NULL;

    // store result from getopt
    int opt;
    while ((opt = getopt(argc, argv, "i:o:ech")) != -1) {
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
            case 'c':
                expandMode = Compress;
                break;
            case '?':
                printf("unrecognized argument: %c\n", optopt);
                break;
            case 'h':
            default:
                printf("usage:\n");
                printf("\texpand a file:   file-expander -e -i <input-filename> -o <output-filename>\n");
                printf("\tunexpand a file: file-expander -c -i <input-filename> -o <output-filename>\n");
                return 0;
        }
    }

    if (expandMode == None) {
        printf("error: must set a mode\n");
        return 1;
    }

    if (inputPath == NULL) {
        printf("error: must supply an input file\n");
        return 1;
    }

    if (outputPath == NULL) {
        printf("error: must supply an output file\n");
        return 1;
    }

    return 0;
}
