INC = ../inc
SRC = ../src
BIN = ../bin
OBJ = ../obj
CFLAGS = -c -g -Wall
LFLAGS = 
GCC = gcc
IFLAGS = -I $(INC)

OBJFILES = $(OBJ)/notes_function_def.o $(OBJ)/calendar_client.o $(OBJ)/choices_def.o $(OBJ)/date_function_def.o 

all : $(BIN)/output

$(BIN)/output : $(OBJFILES)
	$(GCC) -o $(BIN)/output $(OBJFILES)


$(OBJ)/calendar_client.o : $(SRC)/calendar_client.c
	$(GCC) -o $(OBJ)/calendar_client.o $(CFLAGS) $(SRC)/calendar_client.c $(IFLAGS)

$(OBJ)/choices_def.o : $(SRC)/choices_def.c
	$(GCC) -o $(OBJ)/choices_def.o $(CFLAGS) $(SRC)/choices_def.c $(IFLAGS)

$(OBJ)/date_function_def.o : $(SRC)/date_function_def.c
	$(GCC) -o $(OBJ)/date_function_def.o $(CFLAGS) $(SRC)/date_function_def.c $(IFLAGS)

$(OBJ)/notes_function_def.o : $(SRC)/notes_function_def.c
	$(GCC) -o $(OBJ)/notes_function_def.o $(CFLAGS) $(SRC)/notes_function_def.o $(IFLAGS)


clean :
	rm $(BIN)/output
	rm $(OBJ)/*.o
