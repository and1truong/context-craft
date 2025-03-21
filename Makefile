# Compiler and compiler flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O2

# Linker flags
LDFLAGS := -lstdc++fs

# Executable name
TARGET := contextcraft

# Source files
SRCS := contextcraft.cpp

# Object files (automatically generated from source files)
OBJS := $(SRCS:.cpp=.o)

# Default target (build the executable)
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up (remove object files and the executable)
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (targets that are not actual files)
.PHONY: all clean

# --- macOS Specific Build (Conditional) ---
# If on macOS, we try building without -lstdc++fs first,
# and only use it if the first attempt fails.  This is the
# most robust approach for cross-platform compatibility.

ifeq ($(shell uname), Darwin)  # Check if we're on macOS
MACOS_TARGET := contextcraft_macos
MACOS_LDFLAGS :=

$(MACOS_TARGET): $(OBJS)
	@echo "Attempting macOS build without -lstdc++fs..."
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(MACOS_TARGET) $(MACOS_LDFLAGS) 2> /tmp/macos_build_err
	@if [ -s /tmp/macos_build_err ]; then \
		echo "macOS build without -lstdc++fs failed.  Trying with -lstdc++fs..."; \
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(MACOS_TARGET) -lstdc++fs; \
	else \
		echo "macOS build successful."; \
	fi
	@rm -f /tmp/macos_build_err

macos: $(MACOS_TARGET)
.PHONY: macos

endif

# --- Windows Specific Build (MinGW/MSYS2) ---
# For Windows, we assume a MinGW/MSYS2 environment with g++.
# This provides a POSIX-like environment, allowing us to use
# a similar Makefile.

ifeq ($(OS), Windows_NT)  # Check for Windows
WINDOWS_TARGET := contextcraft.exe
WINDOWS_LDFLAGS := -lstdc++fs

$(WINDOWS_TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(WINDOWS_TARGET) $(WINDOWS_LDFLAGS)

windows: $(WINDOWS_TARGET)
.PHONY: windows

endif
