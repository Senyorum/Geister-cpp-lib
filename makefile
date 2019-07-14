CXX = g++
CXXFLAGS = -MMD -MP -w -g -pg -std=c++17 -Ofast -march=native -mtune=native
LIBS = -ldl

ifeq ($(CXX),clang++)
  LIBS += -stdlib=libc++ -lc++experimental -lc++abi -lc++fs
  CXXFLAGS += -fPIC -stdlib=libc++
endif
ifeq ($(CXX),g++)
  CXXFLAGS += -fPIC
endif
OBJ_EXT = o
LIB_EXT = so
EXE_EXT = out

ifeq ($(OS),Windows_NT)
  LIBS =  -lws2_32 -lwsock32 -lwinmm
  OBJ_EXT = obj
  LIB_EXT = dll
  EXE_EXT = exe
endif

ifeq ($(CXX),g++)
  LIBS += -lstdc++fs
endif

PLAYER_NAME = Player
ifdef PLAYER_CLASS
$(shell find ./Player -type f -name \*.hpp | awk -F"/" '{ print $$NF }' | grep -v all.hpp | awk '{print "\#include \"" $$1 "\""}' > Player/all.hpp)
endif
PLAYER_CLASS = RandomPlayer

BIN_DIR = bin
OBJ_DIR = obj
EXIST_BIN_DIR = $(shell find ./ -type d -name $(BIN_DIR) | awk -F"/" '{ print $$NF }')
ifneq ($(EXIST_BIN_DIR),$(BIN_DIR))
$(shell mkdir $(BIN_DIR))
endif
EXIST_OBJ_DIR = $(shell find ./ -type d -name $(OBJ_DIR) | awk -F"/" '{ print $$NF }')
ifneq ($(EXIST_OBJ_DIR),$(OBJ_DIR))
$(shell mkdir $(OBJ_DIR))
endif

VPATH = Player

TARGETS = $(addprefix $(BIN_DIR)/,PlayerTest.$(EXE_EXT) randomPlayer.$(LIB_EXT) chototsuPlayer.$(LIB_EXT) $(PLAYER_NAME).$(EXE_EXT) client.$(EXE_EXT) competition.$(EXE_EXT) $(PLAYER_NAME).$(LIB_EXT))

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/*.*
	
PlayerTest_OBJ = $(addprefix $(OBJ_DIR)/,PlayerTest.$(OBJ_EXT) Geister.$(OBJ_EXT) unit.$(OBJ_EXT))
$(addprefix $(BIN_DIR)/,PlayerTest.$(EXE_EXT)): $(PlayerTest_OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

randomPlayer_OBJ = $(addprefix $(OBJ_DIR)/,randomPlayer.$(OBJ_EXT) Geister.$(OBJ_EXT) unit.$(OBJ_EXT))
$(addprefix $(BIN_DIR)/,randomPlayer.$(LIB_EXT)): $(randomPlayer_OBJ)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

chototsuPlayer_OBJ = $(addprefix $(OBJ_DIR)/,chototsuPlayer.$(OBJ_EXT) Geister.$(OBJ_EXT) unit.$(OBJ_EXT))
$(addprefix $(BIN_DIR)/,chototsuPlayer.$(LIB_EXT)): $(chototsuPlayer_OBJ)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

Player_OBJ = $(addprefix $(OBJ_DIR)/,Player.$(OBJ_EXT) Geister.$(OBJ_EXT) unit.$(OBJ_EXT) Simulator.$(OBJ_EXT))
$(addprefix $(BIN_DIR)/,$(PLAYER_NAME).$(EXE_EXT)): $(Player_OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

$(addprefix $(BIN_DIR)/,$(PLAYER_NAME).$(LIB_EXT)): $(Player_OBJ)
	$(CXX) $(CXXFLAGS) -shared $^ $(LIBS) -o $@

client_OBJ = $(addprefix $(OBJ_DIR)/,client.$(OBJ_EXT) Geister.$(OBJ_EXT) unit.$(OBJ_EXT) tcpClient.$(OBJ_EXT))
$(addprefix $(BIN_DIR)/,client.$(EXE_EXT)): $(client_OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

competition_OBJ = $(addprefix $(OBJ_DIR)/,competition.$(OBJ_EXT) unit.$(OBJ_EXT) Geister.$(OBJ_EXT))
$(addprefix $(BIN_DIR)/,competition.$(EXE_EXT)): $(competition_OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

OBJS = $(addprefix $(OBJ_DIR)/,$(addsuffix .$(OBJ_EXT),client competition PlayerTest unit tcpClient Geister Simulator randomPlayer chototsuPlayer Player))
DEPS   = $(OBJS:.$(OBJ_EXT)=.d)

$(OBJ_DIR)/%.$(OBJ_EXT): %.cpp
	$(CXX) $(CXXFLAGS) -DPLAYER_NAME=$(PLAYER_NAME) -DPLAYER_CLASS=$(PLAYER_CLASS) -I./ -I./lib/ -c $< -o $@

-include $(DEPS)
