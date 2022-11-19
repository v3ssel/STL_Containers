CC = gcc
CFLAGS = -lstdc++ -std=c++17 -Wall -Werror -Wextra
TEST_LIBS = -lgtest

all: tests check

tests: test_array test_list test_map test_queue test_set test_stack test_vector

test_array:
	$(CC) $(CFLAGS) $(TEST_LIBS) array/array_tests.cc -o test.out
	./test.out

test_list:
	$(CC) $(CFLAGS) $(TEST_LIBS) list/list_tests.cc -o test.out
	./test.out

test_map:
	$(CC) $(CFLAGS) $(TEST_LIBS) map/map_tests.cc -o test.out
	./test.out

test_multiset:
	$(CC) $(CFLAGS) $(TEST_LIBS) multiset/multiset_tests.cc -o test.out
	./test.out

test_queue:
	$(CC) $(CFLAGS) $(TEST_LIBS) queue/queue_tests.cc -o test.out
	./test.out

test_set:
	$(CC) $(CFLAGS) $(TEST_LIBS) set/set_tests.cc -o test.out
	./test.out

test_stack:
	$(CC) $(CFLAGS) $(TEST_LIBS) stack/stack_tests.cc -o test.out
	./test.out

test_vector:
	$(CC) $(CFLAGS) $(TEST_LIBS) vector/vector_tests.cc -o test.out
	./test.out

check:
	clang-format -style=Google --dump-config > .clang-format
	clang-format -n array/* \
					list/* \
					map/* \
					multiset/* \
					queue/* \
					set/* \
					stack/* \
					vector/* \
					node.h \
					tree.h

	rm -f .clang-format


clean:
	rm -f test.out
