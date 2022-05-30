hidecmd := @
RM = rm -rf

CXX = g++
CXXFLAGS += -g
CPPFLAGS += -Wall -Wextra -Werror -Wno-missing-field-initializers -Wold-style-cast
CPPFLAGS += -std=gnu++14

BUILD_FOLDER = build

FOLDERS = UI Game

SOURCES := $(wildcard *.cpp) $(foreach dir,$(FOLDERS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst %.cpp,$(BUILD_FOLDER)/%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,$(BUILD_FOLDER)/%.d,$(SOURCES))
HEADERS := $(wildcard *.h) $(wildcard *.hpp) $(foreach dir,$(FOLDERS),$(wildcard $(dir)/*.h)) $(foreach dir,$(FOLDERS),$(wildcard $(dir)/*.hpp))
BUILD_HEADERS := $(addprefix $(BUILD_FOLDER)/, $(HEADERS))
BUILD_HEADERS_CHECK := $(addsuffix .header, $(BUILD_HEADERS))

own_include := UI/ .
sdl_include := $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf
include := $(addprefix -I, $(own_include)) $(sdl_include)

EXECUTABLE = out

.PHONY: all clean run valgrind-create valgrind
.SECONDEXPANSION:
.SECONDARY:

all: $$(EXECUTABLE)

run: $$(EXECUTABLE)
		@./$(EXECUTABLE)

valgrind: $$(EXECUTABLE) ./minimal.supp
		@valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./minimal.supp ./$(EXECUTABLE)

valgrind-create: $$(EXECUTABLE)
		@valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./minimal.supp --gen-suppressions=all --log-file=minimalraw.log ./$(EXECUTABLE)
		@cat ./minimalraw.log | ./suppressions.sh >> minimal.supp

clean:
		@echo "[CLEAN UP]"
		$(hidecmd)$(RM) $(BUILD_FOLDER) $(EXECUTABLE)

$(EXECUTABLE): $$(OBJECTS) $$(BUILD_HEADERS_CHECK)
		@echo "[LINK] $(patsubst $(BUILD_FOLDER)/%,%,$(OBJECTS))"
		$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(include)

$(BUILD_FOLDER)/%.o: %.cpp | $$(@D)/.dir
		@echo "[C++ ] $<"
		$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@ $(include)

$(BUILD_HEADERS_CHECK): $(BUILD_FOLDER)/%.header: % | $$(@D)/.dir
		@echo "[HDR ] $<"
		$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Wno-unused-const-variable -c -fsyntax-only $< $(include)
		@touch $@

%/.dir:
		@echo "[DIR ] $(@D)"
		@mkdir -p $(@D) && touch $@

-include $(DEPENDS)
