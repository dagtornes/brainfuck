CFLAGS=-Wall -g

SRC=brainfuck.c bfscan.c
OBJ=$(patsubst %.c,%.o,$(SRC))

TEST_SRC=bfscan.c test_brainfuck.c
TEST_OBJ=$(patsubst %.c,%.o,$(TEST_SRC))

TARGET=brainfuck
TEST=test_$(TARGET)

all: $(TARGET)

test: $(TEST)

$(TARGET): $(OBJ)

$(TEST): LDFLAGS += -lcmocka
$(TEST): $(TEST_OBJ)

clean:
	rm -f $(TARGET) *.o
	rm -rf *.dSYM
