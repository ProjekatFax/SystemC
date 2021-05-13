SHELL=/bin/bash

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

SYSTEMC = /home/systemC

FILE_NAME = zadatak1

args:
	FILE_NAME = args


all: ${FILE_NAME} #${FILE_NAME}_d 

${FILE_NAME}: ${FILE_NAME}.cpp
	g++ -I ${SYSTEMC}/include/ -L ${SYSTEMC}/lib-linux64/ -l:libsystemc.a -lpthread -o ${FILE_NAME} ${FILE_NAME}.cpp

#${FILE_NAME}_d: ${FILE_NAME}.cpp
#	g++ -I ${SYSTEMC}/include/ -L ${SYSTEMC}/lib-linux64/ -lsystemc -o ${FILE_NAME}_d ${FILE_NAME}.cpp

.PHONY: clean
clean:
	rm ${FILE_NAME}_*