CC+FLAGS = gcc -std=c11 -Wall -Wextra -Werror
GCOV_FLAGS = -L. --coverage -ls21_matrix

OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -lm -pthread -lrt -lsubunit
	OPEN_CMD = xdg-open
	MEM_CHECK = valgrind --tool=memcheck --trace-children=yes --track-origins=yes --leak-check=full
else
	CHECK_FLAGS = -lcheck
	OPEN_CMD = open
	MEM_CHECK = leaks --atExit -- ./s21_test
endif

all: clean test gcov_report

test: s21_matrix.a
	$(CC+FLAGS) s21_tests.c s21_matrix.a $(CHECK_FLAGS) -L. -ls21_matrix -o s21_test
	./s21_test

gcov_report: s21_matrix.a
	$(CC+FLAGS) *.c s21_matrix.a $(CHECK_FLAGS) $(GCOV_FLAGS) -o s21_test
	./s21_test
	lcov -t s21_test -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html
	make clean_test

s21_matrix.a: s21_matrix.o
	ar rcs libs21_matrix.a *.o
	rm -rf *.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a
	cp libs21_matrix.a ls21_matrix.a

s21_matrix.o:
	$(CC+FLAGS) -c s21_matrix.c

check:
	make test
	CK_FORK=no $(MEM_CHECK) ./s21_test
	make clean

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format

clean_obj:
	rm -rf *.o *.a

clean_test: clean_obj
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf s21_test

clean: clean_test
	rm -rf s21_test
	rm -rf report