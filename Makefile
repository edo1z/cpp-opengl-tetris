CPPFLAGS := -g -Wall -std=c++17 -I src/includes -I ${CPATH}
FRAMEWORKS := -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LIBS := -L ${LIBRARY_PATH} -lglfw -lGLEW

BUILD_DIR := ./bin
SRC_DIRS := ./src
SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(addprefix $(BUILD_DIR)/, $(subst .cpp,.o, $(notdir $(SRCS))))

$(BUILD_DIR)/main: $(OBJS)
	clang++ -o $@ $(LIBS) $(FRAMEWORKS) $^ 
$(BUILD_DIR)/debug: $(OBJS)
	clang++ -o $@ $(LIBS) $(FRAMEWORKS) $^ 
$(BUILD_DIR)/%.o: src/%.cpp
	clang++ -c -o $@ $(CPPFLAGS) $<

do:
	@bin/main
clean:
	rm -rf bin
	mkdir bin

