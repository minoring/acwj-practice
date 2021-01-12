CC = cc
DEPS = data.h decl.h defs.h
SRCS = cg.c decl.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c types.c

comp1: $(SRCS) $(DEPS)
	$(CC) -o comp1 -g $(SRCS)

clean:
	rm -f comp1 *.o *.s out

# test: comp1 tests/runtests
# 	(cd tests; chmod +x runtests; ./runtests)

t: comp1 tests/input$(N).c lib/printint.c
	./comp1 tests/input$(N).c

