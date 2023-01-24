CC = g++

ifdef OS
	MAIN = .\bin\main.exe
	INCS = .\src\cliui.h .\src\evaluate_exp.h .\src\generate_exp.h .\src\generate_perms.h
	SRCS = .\src\cliui.cpp .\src\evaluate_exp.cpp .\src\generate_exp.cpp .\src\generate_perms.cpp .\src\main.cpp
else
	ifeq ($(shell uname), Linux)
		MAIN = ./bin/main.exen.cpp
		INCS = ./src/cliui.h ./src/evaluate_exp.h ./src/generate_exp.h ./src/generate_perms.h
		SRCS = ./src/cliui.cpp ./src/evaluate_exp.cpp ./src/generate_exp.cpp ./src/generate_perms.cpp ./src/main.cpp
	endif
endif

.PHONY: all compile

all: compile

compile:
	g++ $(SRCS) $(INCS) -o $(MAIN)