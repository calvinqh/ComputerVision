########################################
##
## Makefile
## LINUX compilation 
##
##############################################

#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)
Cpp_OBJ=image.o image_demo.o create_binary_image.o create_labeled_image.o compute_attributes.o classify_instances.o 
Cpp_OBJ_1=image.o p1.o create_binary_image.o create_labeled_image.o compute_attributes.o classify_instances.o 
Cpp_OBJ_2=image.o p2.o create_binary_image.o create_labeled_image.o compute_attributes.o classify_instances.o 
Cpp_OBJ_3=image.o p3.o create_binary_image.o create_labeled_image.o compute_attributes.o classify_instances.o 
Cpp_OBJ_4=image.o p4.o create_binary_image.o create_labeled_image.o compute_attributes.o classify_instances.o 

#Demo
PROGRAM_NAME=image_demo
$(PROGRAM_NAME): $(Cpp_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ) $(INCLUDES) $(LIBS_ALL)

#Program One
PROGRAM_ONE=p_1
$(PROGRAM_ONE): $(Cpp_OBJ_1) 
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

#Program Two
PROGRAM_TWO=p_2
$(PROGRAM_TWO): $(Cpp_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)


#Program Three
PROGRAM_THREE=p_3
$(PROGRAM_THREE): $(Cpp_OBJ_3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_3) $(INCLUDES) $(LIBS_ALL)


#Program Four
PROGRAM_FOUR=p_4
$(PROGRAM_FOUR): $(Cpp_OBJ_4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_4) $(INCLUDES) $(LIBS_ALL)

all: p1 p2 p3 p4

p1:
	make $(PROGRAM_ONE)

p2:
	make $(PROGRAM_TWO)

p3:
	make $(PROGRAM_THREE)

p4:
	make $(PROGRAM_FOUR)

clean:
	(rm -f *.o;)

(:
