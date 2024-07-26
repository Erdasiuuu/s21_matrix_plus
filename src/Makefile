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

valgrind: $(TARGET) test
	valgrind --trace-children=yes --track-origins=yes --leak-check=full ./test > valgrind_log.txt 2>&1

clang-format:
	clang-format -style=Google -n $(SOURCES)
	clang-format -style=Google -i $(SOURCES)

clean:
	rm -rf ./*.o ./*.a gcov_test ./*.gcno ./*.gcda report/ ./test ./test.c ./*.info valgrind_log.txt

rebuild: clean all
