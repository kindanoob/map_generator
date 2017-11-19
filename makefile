INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
SFML_DIR = # put your SFML directory here (for example: /home/dev_libs/SFML-2.4.2)
SFML_INC = $(SFML_DIR)/include/
SFLM_LIB_LOC = $(SFML_DIR)/lib/
CXX = g++ -std=c++11
DEBUG = -O0 -g
CXXFLAGS = -Wall -c $(DEBUG) -I$(INC_DIR)
LDFLAGS = -Wall $(DEBUG)
SFML_LIBS =  -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
HEADERS = $(wildcard $(INC_DIR)/*.h)
EXECUTABLE_TARGET = map_generator


all: $(EXECUTABLE_TARGET)

$(EXECUTABLE_TARGET): $(OBJECTS)
	$(CXX) -o $(EXECUTABLE_TARGET) $(OBJECTS) $(LDFLAGS) -L$(SFLM_LIB_LOC) $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(SFML_INC) -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)