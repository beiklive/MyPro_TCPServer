#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件

THIRD	:= ./src/3rd
FUNC	:= ./src/func
OBJS_DIR := ./build/

SOURCE  := $(wildcard *.cpp) $(wildcard ${FUNC}/*.cpp)
# OBJS    := $(addprefix $(OBJS_DIR), $(patsubst %.cpp,%.o,$(notdir $(SOURCE))))
OBJS    := $(patsubst %.cpp,%.o,$(SOURCE))

#target you can change test to what you want
#目标文件名，输入任意你想要的执行文件名
TARGET  := main
  
#compile and lib parameter
#编译参数
CC      := g++
LIBS    :=
LDFLAGS := -lpthread
DEFINES :=
INCLUDE := -I${THIRD} -I${FUNC}
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE) $(LDFLAGS)
  
#i think you should do anything here
#下面的基本上不需要做任何改动了
$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)


%.o:%.cpp
	$(CC) -c $^ -o  $@ $(CFLAGS)
  

.PHONY: clean run

run : $(TARGET)
	@./$(TARGET)


clean :
	rm -fr $(TARGET).o
	rm -fr $(TARGET)
	rm -fr ${FUNC}/*.o

    
