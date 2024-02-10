CXX = g++
CXXFLAGS = -std=c++20

SRC_DIR = src
BIN_DIR = bin

# List of source files
SRCS = $(SRC_DIR)/main.cpp

# Output binary
TARGET = app

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^

clean:
	rm -f $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TARGET).exe

run: 
	$(BIN_DIR)/$(TARGET)

runs: clean all
	$(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TARGET).exe
