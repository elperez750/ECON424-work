# Usage:   make test        run every stage's tests
#          make t1          run just Stage 1  (t0 ... t5)
#          make clean
CC      ?= gcc
CFLAGS  = -std=c99 -Wall -Wextra -Wno-unused-parameter -g -Isrc -Itests -fsanitize=address,undefined
LDLIBS  = -lm
SRC     = $(wildcard src/*.c)
HDR     = $(wildcard src/*.h) tests/check.h tests/expected.h
TESTS   = test0_dist test1_stats test2_matrix test3_ols test4_formulas test5_applied

build/%: tests/%.c $(SRC) $(HDR)
	@mkdir -p build
	$(CC) $(CFLAGS) $< $(SRC) -o $@ $(LDLIBS)

t0: build/test0_dist
	./build/test0_dist
t1: build/test1_stats
	./build/test1_stats
t2: build/test2_matrix
	./build/test2_matrix
t3: build/test3_ols
	./build/test3_ols
t4: build/test4_formulas
	./build/test4_formulas
t5: build/test5_applied
	./build/test5_applied

test:
	@for t in $(TESTS); do $(MAKE) --no-print-directory build/$$t >/dev/null && ./build/$$t; echo; done

clean:
	rm -rf build

.PHONY: t0 t1 t2 t3 t4 t5 test clean
