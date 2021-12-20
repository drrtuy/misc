SOURCE=ltl.cpp test.cpp
TARGET=test

CFLAGS = -I. -g3 -Wall

all: $(TARGET)

$(TARGET): $(SOURCE)
	g++ $(CFLAGS) -o $@ -I. $^

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET)

