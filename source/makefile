#
# MIT License
# Copyright (c) 2018, Michal Kozakiewicz, github.com/michal037
#
# Version: 2.0.0
# Standard: GCC-C11
#

OUTNAME=lcdtest
EXAMPLE=main.cpp

CC=gcc
CFLAGS=-Wall 
SOURCES=st7735s.h st7735s.cpp 
LIBS=-lwiringPi

.PHONY: help compile clean run

help:
	@echo "MAKEFILE HELP:\n Use:\n  make compile/run/clean/help"

compile:
	$(CXX) $(LIBS) $(CFLAGS) -o $(OUTNAME) $(SOURCES) $(EXAMPLE)

clean:
	rm -rf $(OUTNAME)

run: clean compile
	./$(OUTNAME)
