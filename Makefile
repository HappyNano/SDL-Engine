hidecmd := @
RM = rm -rf

CXX = g++
CXXFLAGS += -g
CPPFLAGS += -Wall -Wextra -Werror -Wno-missing-field-initializers -Wold-style-cast
CPPFLAGS += -std=gnu++14

BUILD_FOLDER = build

SOURCES := $(wildcard *.cpp) $(wildcard UI/*.cpp) 
OBJECTS := $(patsubst %.cpp,$(BUILD_FOLDER)/%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,$(BUILD_FOLDER)/%.d,$(SOURCES))
HEADERS := $(wildcard *.h) $(wildcard UI/*.h) $(wildcard *.hpp) $(wildcard UI/*.hpp)
BUILD_HEADERS := $(addprefix $(BUILD_FOLDER)/, $(HEADERS))
BUILD_HEADERS_CHECK := $(addsuffix .header, $(BUILD_HEADERS))

own_include := UI/
include := $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf

EXECUTABLE = out

.PHONY: all clean run valgrind-create valgrind

all: $(EXECUTABLE)

run: $(EXECUTABLE)
		@./$(EXECUTABLE)

valgrind: $(EXECUTABLE) ./minimal.supp
		@valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./minimal.supp ./$(EXECUTABLE)

valgrind-create: $(EXECUTABLE)
		@valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./minimal.supp --gen-suppressions=all --log-file=minimalraw.log ./$(EXECUTABLE)
		@cat ./minimalraw.log | ./suppressions.sh >> minimal.supp

clean:
		@echo "[CLEAN UP]"
		$(hidecmd)$(RM) $(OBJECTS) $(DEPENDS) $(EXECUTABLE) $(BUILD_HEADERS_CHECK)

$(EXECUTABLE): $(OBJECTS) $(BUILD_HEADERS_CHECK)
		@echo "[LINK] $(patsubst $(BUILD_FOLDER)/%,%,$(OBJECTS))"
		$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(include)

$(BUILD_FOLDER)/%.o: %.cpp Makefile
		@echo "[C++ ] $<"
		$(hidecmd)$(CXX) $(CPPFLAGS) $(addprefix -I, $(own_include)) $(CXXFLAGS) -MMD -MP -c $< -o $@ $(include)

$(BUILD_HEADERS_CHECK): $(BUILD_FOLDER)/%.header: %
		@echo "[HDR ] $<"
		$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(addprefix -I, $(own_include)) -Wno-unused-const-variable -c -fsyntax-only $< $(include)
		@touch $@

-include $(DEPENDS)
