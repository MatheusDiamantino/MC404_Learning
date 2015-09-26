##########################################################
# Description: Template to build the makefile for
#   "trab01".
#
# Author: Edson Borin - edson@ic.unicamp.br
#
# 1) You may add more files to your project changing the 
#    OBJ_FILES list.
#
# 2) You may remove or add new rules to compile your .c files 
#    (see as an example rules main.o and error.o)
#
# 3) You may not change the ias-as rule (do not add 
#    extra libraries!)
#
##########################################################

# List of object files that must be linked together to 
# build the ias-as executable
OBJ_FILES=main.o labelBST.o readInput.o treat_type.o treat_MMP.o memory_map_BST.o identifier.o treat_error.o

# Default rule
all: ias-as

# -- Rules for making each one of the .o files --

# -- main.o
main.o: main.c labelBST.h identifier.h typeEnum.h instruction.h defines.h memory_map_BST.h treat_type.h
	gcc -c -g main.c -o main.o

# -- labelBST.o depends on labelBST.c and on labelBST.h
labelBST.o: labelBST.c labelBST.h
	gcc -c -g labelBST.c -o labelBST.o

# —- readInput.o
readInput.o: readInput.c readInput.h treat_error.h
	gcc -c -g readInput.c -o readInput.o

# —- treat_type.o
treat_type.o: treat_type.c treat_type.h treat_MMP.h labelBST.h defines.h readInput.h instruction.h identifier.h memory_map_BST.h treat_error.h
	gcc -c -g treat_type.c -lm -o treat_type.o

# —- treat_MMP.o
treat_MMP.o: treat_MMP.c treat_MMP.h defines.h
	gcc -c -g treat_MMP.c -o treat_MMP.o

# —- memory_map_BST.o
memory_map_BST.o: memory_map_BST.c memory_map_BST.h
	gcc -c -g memory_map_BST.c -o memory_map_BST.o

# —- identifier.o
identifier.o: identifier.c identifier.h typeEnum.h readInput.h labelBST.h instruction.h treat_type.h treat_MMP.h treat_error.h
	gcc -c -g identifier.c -o identifier.o

# —- treat_error.o
treat_error.o: treat_error.c treat_error.h defines.h
	gcc -c -g treat_error.c -o treat_error.o

# -- Clean rule. It removes the ias-as file and any .o file on the directory --
clean:
	rm -f ias-as *.o

##########################################################
# Do not change this rule
##########################################################

# -- Rule to make the executable ias-as
ias-as: $(OBJ_FILES)
	gcc -g $(OBJ_FILES) -o ias-as 