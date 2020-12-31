SRCS = cg.c decl.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c interp.c types.c
comp1: $(SRCS)
	cc -o comp1 -g $(SRCS)

clean:
	rm -f comp1 *.o *.s out

test: comp1 tests/runtests.sh
		(cd tests; chmod +x runtests.sh; ./runtests.sh)

test10: comp1 tests/input10
	./comp1 tests/input10

