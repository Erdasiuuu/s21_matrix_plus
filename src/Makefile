CC=g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TEST_LIBS = -lgtest
SOURCES = $(wildcard s21_matrix_oop/s21_*.cc)
OS = $(shell uname)
GCOV_FLAG = --no-external

TARGET=s21_matrix_oop.a

ifneq ($(OS), Darwin)
	TEST_LIBS = -lgtest -lsubunit -pthread -lrt -lm
	GCOV_FLAG =
endif

all: $(TARGET) test gcov_report

$(TARGET):
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rcs $(TARGET) *.o

test: $(TARGET)
	$(CC) $(CFLAGS) --coverage $(SOURCES) test.cc $(TARGET) $(TEST_LIBS) -o test
	./test	
	
gcov_report: test
	lcov -o gcov_test.info $(GCOV_FLAG) -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

clean:
	rm -rf ./*.o ./*.a gcov_test ./*.gcno ./*.gcda report/ ./test ./test.c ./*.info

clang-format:
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h


rebuild: clean all
