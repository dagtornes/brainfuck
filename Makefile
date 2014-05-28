CFLAGS=-Wall -g -std=c99 -Isrc/ -MMD

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o,$(SRC))

TEST_SRC=$(wildcard testsrc/*.c)
TEST_OBJ=$(patsubst testsrc/%.c,obj/%.o,$(TEST_SRC))

TARGET=brainfuck
TEST=test_$(TARGET)

all: $(TARGET)

test: $(TEST)

obj/%.o: testsrc/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

$(TEST): LDFLAGS += -lcmocka
$(TEST): $(TEST_OBJ) $(filter-out obj/$(TARGET).o, $(OBJ))
	$(CC) -o $@ $^ $(LDFLAGS)
	./$(TEST)

clean:
	rm -f $(TARGET)
	rm -f obj/*.o
	rm -rf *.dSYM
