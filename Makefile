# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Libraries
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Source files
SRCS = src/main.cpp src/zoom.cpp src/directory.cpp

# Output executable
TARGET = imvi

# Installation paths
INSTALL_DIR = /usr/local/bin
SHARE_DIR = /usr/share/imvi

# Build rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)
                                          

# Clean rule
clean:
	rm -f $(TARGET)

# Install rule
install: $(TARGET)
	mkdir -p $(INSTALL_DIR)
	mkdir -p $(SHARE_DIR)
	cp $(TARGET) $(INSTALL_DIR)/
	cp images/ico.png $(SHARE_DIR)/ico.png
	@echo "Installed $(TARGET) to $(INSTALL_DIR)"
	@echo "Installed icon to $(SHARE_DIR)"

# Uninstall rule
uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)
	rm -rf $(SHARE_DIR)
	@echo "Uninstalled $(TARGET)"