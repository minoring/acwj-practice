#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

// Initialise global variables
static void init() {
    Line = 1;
    Putback = '\n';
    Globs = 0;
    Locls = NSYMBOLS - 1;
    O_dumpAST = 0;
}

// Print out a usage if started incorrectly
static void usage(char *prog) {
    fprintf(stderr, "Usage: %s [-T] inflie\n", prog);
    exit(1);
}

// Main program: check arguments and print a usage
// if we don't have an argument.
int main(int argc, char *argv[]) {
    int i;

    init();

    // Scan for command-line options
    for (i = 1; i < argc; i++) {
        if (*argv[i] != '-') {
            break;
        }
        for (int j = 1; j < argv[i][j]; j++) {
            switch (argv[i][j]) {
            case 'T':
                O_dumpAST = 1;
                break;
            default:
                usage(argv[0]);
            }
        }
    }

    // Ensure we have an input file argument.
    if (i >= argc) {
        usage(argv[0]);
    }


    if ((Infile = fopen(argv[i], "r")) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    // Create the output file
    if ((Outfile = fopen("out.s", "w")) == NULL) {
        fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
        exit(1);
    }

    // For now, ensure that printint() and printchar() are defined.
    addglob("printint", P_CHAR, S_FUNCTION, C_GLOBAL, 0, 0);
    addglob("printchar", P_VOID, S_FUNCTION, C_GLOBAL, 0, 0);

    scan(&Token); // Get the first token from the input
    genpreamble();
    global_declarations();
    genpostamble();
    fclose(Outfile);
    exit(0);
}
