CC = cc
DEPS = data.h decl.h defs.h
SRCS = cg.c decl.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c types.c

comp1: $(SRCS) $(DEPS)
	$(CC) -o comp1 -g $(SRCS)

clean:
	rm -f comp1 *.o *.s out

test: comp1 tests/runtests.sh
		(cd tests; chmod +x runtests.sh; ./runtests.sh)

test15: comp1 tests/input15.c lib/printint.c
	./comp1 tests/input15.c

