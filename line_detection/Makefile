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
Cpp_OBJ = image.o hough_lines.o edge_detection.o
Cpp_OBJ_1 = image.o hough_lines.o edge_detection.o h1.o
Cpp_OBJ_2 = image.o hough_lines.o edge_detection.o h2.o
Cpp_OBJ_3 = image.o hough_lines.o edge_detection.o h3.o
Cpp_OBJ_4 = image.o hough_lines.o edge_detection.o h4.o

PROGRAM_1 = h_1
$(PROGRAM_1): $(Cpp_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

PROGRAM_2 = h_2
$(PROGRAM_2): $(Cpp_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)

PROGRAM_3 = h_3
$(PROGRAM_3): $(Cpp_OBJ_3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_3) $(INCLUDES) $(LIBS_ALL)

PROGRAM_4 = h_4
$(PROGRAM_4): $(Cpp_OBJ_4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_4) $(INCLUDES) $(LIBS_ALL)

all:  h1 h2 h3 h4

h1:
	make $(PROGRAM_1)
h2:
	make $(PROGRAM_2)
h3:
	make $(PROGRAM_3)
h4:
	make $(PROGRAM_4)

clean:
	(rm -f *.o;)

r1:
	./h_1 hough_simple_2.pgm str_1.pgm

r2:
	./h_2 str_1.pgm 20 str_2.pgm

r3:
	./h_3 str_2.pgm hough.pgm data.txt 

r4:
	./h_4 hough_simple_2.pgm data.txt 200 line.pgm
r5:
	./h_4 hough_simple_2.pgm data.txt 120 line.pgm | more
r6:
	./h_4 hough_simple_2.pgm data.txt 160 line.pgm | more
r7:
	./h_2 str_1.pgm 160 str_2.pgm




(:
