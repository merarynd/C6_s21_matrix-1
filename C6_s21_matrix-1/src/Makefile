OS :=$(shell uname -s)
NAME :=$(shell whoami)
GC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -g
TEST=../tests/test
TEST_NOT=../tests/testest
LIB=s21_decimal
SPEC=special
COM=common
GCOV=--coverage
SANI=-fsanitize=address -g
#  цвета
BLUE=\033[96m
RED=\033[91m
END=\033[0m

ifeq ($(OS), Darwin)
	FLAGS_PLATFORM =-lcheck
else
	FLAGS_PLATFORM =-lcheck -lsubunit -lrt -lm -lpthread -g
endif

all : out

clean :
	@echo "$(BLUE)-------------CLEAN-------------$(END)"
	@rm -rf *.o
	@rm -rf *.a
	@rm -rf *.g*
	@rm -rf report
	@rm -rf test.info
	@rm -rf gcov
	@rm -rf f
	@rm -rf tests
	@rm -rf ../tests/*.o

test_not : clean $(LIB).a $(TEST).o
	@echo "$(BLUE)---------RUNNING TESTS---------$(END)"
	@$(GC) $(CFLAGS) $(TEST).o -l check -L. $(LIB).a $(FLAGS_PLATFORM) -o tests
	@./tests > 2.txt
	@echo "$(BLUE)-------------------------------$(END)"

test : clean $(LIB).a $(TEST_NOT).o
	@echo "$(BLUE)---------RUNNING TESTS---------$(END)"
	@$(GC) $(CFLAGS) $(TEST_NOT).o -l check -L. $(LIB).a $(FLAGS_PLATFORM) -o tests
	@./tests > 2.txt
	@echo "$(BLUE)-------------------------------$(END)"

# test: s21_decimal.a
# 	$(GC) s21_decimal.a test_hettiehe/*.c $(FLAGS_PLATFORM) -o s21_test -L. -ls21_decimal
# 	./s21_test

$(TEST).o : $(TEST).c
	@$(GC) $(CFLAGS) -c $(TEST).c -o $(TEST).o

$(TEST_NOT).o : $(TEST_NOT).c
	@$(GC) $(CFLAGS) -c $(TEST_NOT).c -o $(TEST_NOT).o


# библиотека для теста
$(LIB).a : $(LIB).c $(COM).c # $(SPEC).c
	@echo "$(BLUE)------------LIBRARY------------$(END)"
	@$(GC) -g -c $(LIB).c $(COM).c $(SPEC).c
	@ar rc $(LIB).a $(LIB).o $(COM).o $(SPEC).o
	@ranlib $(LIB).a

#gcov
gcov_report : clean lcov $(TEST).o g$(LIB).a
	@echo "$(BLUE)----------GCOV REPORT----------$(END)"
	@$(GC) $(GCOV) $(TEST).o -l check -L. $(LIB).a -o gcov
	@./gcov
	@gcov $(LIB).c
	@~/goinfre/homebrew/bin/lcov -t "test" -o test.info -c -d .
	@~/goinfre/homebrew/bin/genhtml -o report test.info
	@open report/index.html
	@echo "$(BLUE)-------------------------------$(END)"

# библиотека для отчета
g$(LIB).a : $(LIB).c $(COM).c # $(SPEC).c
	@echo "$(BLUE)----------COMPILATION----------$(END)"
	@$(GC) $(GCOV) -c $(LIB).c 
	@$(GC) $(GCOV) -c $(COM).c 
	@$(GC) $(GCOV) -c $(SPEC).c
	@ar rc $(LIB).a $(LIB).o $(COM).o $(SPEC).o
	@ranlib $(LIB).a

# проверки lcov и brew
lcov:
ifeq ("", "$(wildcard ~/goinfre/homebrew/bin/lcov)")
	$(error Need to install lcov: make lcov_install)
endif

lcov_install :  brew
	@brew install lcov

brew:
ifeq ("", "$(wildcard ~/goinfre/homebrew)")
	@git clone https://github.com/Homebrew/brew ~/goinfre/homebrew
	@echo "$(RED)Выполните eval \"\$$(/opt/goinfre/*/homebrew/bin/brew shellenv)\"$(END)"
#   curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
endif

out: f
	@echo "$(BLUE)----------COMPILATION----------$(END)"
	@./f > 1.txt
	@echo "$(BLUE)-------------------------------$(END)"

# мой мейник
f : clean f.o $(LIB).a 
	@$(GC) $(CFLAGS) f.o  -L. $(LIB).a $(FLAGS_PLATFORM) -o f

f.o : f.c
	@$(GC) $(CFLAGS) -c f.c