CC = gcc
CXX= g++
LD = ld
CFLAGS = -I/usr/local/include
LDFLAGS=-lPocoNet -lPocoFoundation -lPocoDataMySQL -lPocoData -lPocoDataSQLited
CXXFLAGS += -I/usr/local/include
#find all the sub-directory
#VPATH=$(foreach dir,$(shell find . -type d),$(shell echo $(dir):))
#include all the sub-directory
#INCLS=$(foreach dir,$(subst :, ,$(VPATH)),$(shell echo -I$(dir)))
#find all .c and produce .o
#C_SRC_PATH = $(foreach dir,$(subst :, ,$(VPATH)),$(wildcard $(dir)/*.c))
#COBJS = $(subst .c,.o,$(C_SRC_PATH))
#find all .cxx and produce .o
#CPP_SRC_PATH = $(foreach dir,$(subst :, ,$(VPATH)),$(wildcard $(dir)/*.cxx))
#CPPOBJS = $(subst .cxx,.o,$(CPP_SRC_PATH))
MODULE_NAME=reactor

CSOURCE = $(wildcard *.c)
COBJS = $(patsubst %.c,%.o,$(CSOURCE))
CPPSOURCE = $(wildcard *.cpp)
CPPOBJS = $(patsubst %.cpp,%.o,$(CPPSOURCE))

execobjs = $(COBJS) $(CPPOBJS)
#the scripts for compile
.PHONY: all
all: $(execobjs)
	$(CXX) -o $(MODULE_NAME) $(execobjs) $(LDFLAGS)

$(COBJS):%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(CPPOBJS):%.o:%.cpp
	$(CC) -c $< -o $@ $(CXXFLAGS)
#the scripts for clean
.PHONY: clean

clean:
	@rm $(MODULE_NAME) 
	@rm $(execobjs)
