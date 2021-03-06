#include "defs.h"
#include "data.h"
#include "decl.h"

// Determine if the symbol s is in the global symbol table.
// Return its slot position or -1 if not found.
// Skip C_PARAM entries.
int findglob(char *s) {
    int i;

    for (i = 0; i < Globs; ++i) {
        if (Symtable[i].class == C_PARAM) {
            continue;
        }
        if (*s == *Symtable[i].name && !strcmp(s, Symtable[i].name)) {
            return (i);
        }
    }
    return (-1);
}

// Get the position of a new global symbol slot, or die
// if we've run out of positions.
static int newglob(void) {
    int p;

    if ((p = Globs++) >= Locls) {
        fatal("Too many global symbols");
    }
    return (p);
}

// Determine if the symbol s is in the local symbol table.
// Return its slot position or -1 if not found.
int findlocl(char *s) {
    int i;

    for (i = Locls + 1; i < NSYMBOLS; ++i) {
        if (*s == *Symtable[i].name && !strcmp(s, Symtable[i].name)) {
            return (i);
        }
    }
    return (-1);
}

// Get the position of a new local symbol slot, or die
// if we've run out of positions.
static int newlocl(void) {
    int p;

    if ((p = Locls--) <= Globs) {
        fatal("Too many local symbols");
    }
    return (p);
}

// Clear all the entries in the
// local symbol table.
void freeloclsyms(void) {
    Locls = NSYMBOLS - 1;
}

// Update a symbol at the given slot number in the symbol table.
static void updatesym(int slot, char *name, int type, int stype,
                      int class, int endlabel, int size, int posn) {
    if (slot < 0 || slot >= NSYMBOLS) {
        fatal("Invalid symbol slot number in updatesym()");
    }
    Symtable[slot].name = strdup(name);
    Symtable[slot].type = type;
    Symtable[slot].stype = stype;
    Symtable[slot].class = class;
    Symtable[slot].endlabel = endlabel;
    Symtable[slot].size = size;
    Symtable[slot].posn = posn;
}


// Add a global symbol to the symbol table.
// Return the slot number in the symbol table, -1 if a duplicate entry.
int addglob(char *name, int type, int stype, int class, int endlabel, int size) {
    int slot;

    // If this is already in the symbol table, return the existing slot.
    if ((slot = findglob(name)) != -1) {
        return (slot);
    }

    // Otherwise get a new slot and fill it in.
    slot = newglob();
    updatesym(slot, name, type, stype, class, endlabel, size, 0);
    // Generate the assembly for the symbol if it's global.
    if (class == C_GLOBAL) {
        genglobsym(slot);
    }
    return (slot);
}

// Add a local symbol to the symbol table.
// Return the slot number in the symbol table, -1 if a duplicate entry.
int addlocl(char *name, int type, int stype, int class, int size) {
    int localslot;

    // If this is already in the symbol table, return an error.
    localslot = findlocl(name);
    if (localslot != -1) {
        printf("HIHIHI");
        return (-1);
    }

    // Otherwise get a new symbol slot and a position for this local.
    // Update the local symbol table entry.
    localslot = newlocl();
    updatesym(localslot, name, type, stype, class, 0, size, 0);

    return (localslot);
}

// Given a function's slot number, copy the global parameters
// from its prototype to be local parameter.
void copyfuncparams(int slot) {
    int i, id = slot + 1;

    for (i = 0; i < Symtable[slot].nelems; ++i, ++id) {
        addlocl(Symtable[id].name, Symtable[id].type, Symtable[id].stype,
                Symtable[id].class, Symtable[id].size);
    }
}

// Determine if the symbol s in the symbol table.
// Return its slot position or -1 if not found.
int findsymbol(char *s) {
    int slot;

    slot = findlocl(s);
    if (slot == -1) {
        slot = findglob(s);
    }
    return (slot);
}
