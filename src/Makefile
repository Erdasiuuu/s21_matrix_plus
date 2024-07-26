CC=g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TEST_LIBS = -lgtest
SOURCES = $(wildcard s21_matrix_oop/s21_*.cc)
OS = $(shell uname)
GCOV_FLAG = --no-external

TARGET=s21_matrix_oop.a

ifneq ($(OS), Darwin)
	TEST_LIBS = -lgtest -pthread -lrt
	GCOV_FLAG =
endif

all: $(TARGET) test gcov_report

$(TARGET):
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rcs $(TARGET) *.o

test: $(TARGET)
	$(CC) $(CFLAGS) --coverage $(SOURCES) test.cc $(TARGET) $(TEST_LIBS) -o test
	./test

debug: $(TARGET)
	$(CC) $(SOURCES) test.cc $(TARGET) $(TEST_LIBS) -o test -g

gcov_report: test
	lcov -o gcov_test.info $(GCOV_FLAG) -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

valgrind: $(TARGET) debug
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test > valgrind_log.txt 2>&1

clang-format:
	clang-format -style=Google -n $(SOURCES)
	clang-format -style=Google -i $(SOURCES)

clean:
	rm -rf ./*.o ./*.a gcov_test ./*.gcno ./*.gcda report/ ./test ./test.c ./*.info valgrind_log.txt

rebuild: clean all
