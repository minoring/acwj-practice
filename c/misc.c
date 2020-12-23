#include "defs.h"
#include "data.h"
#include "decl.h"

// Ensure that the current token is t,
// and fetch the next token. Otherwise
// throw an error
void match(int t, char *what) {
    if (Token.token == t) {
        scan(&Token);
    } else {
        printf("%s expected on line %d\n", what, Line);
    }
}

// Match a semicolon and fetch the text token
void semi(void) {
    match(T_SEMI, ";");
}
