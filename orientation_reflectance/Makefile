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
Cpp_OBJ = image.o sphere_feature.o light_sources.o
Cpp_OBJ_1 = image.o sphere_feature.o light_sources.o s1.o
Cpp_OBJ_2 = image.o sphere_feature.o light_sources.o s2.o
Cpp_OBJ_3 = image.o sphere_feature.o light_sources.o s3.o
Cpp_OBJ_4 = image.o sphere_feature.o light_sources.o s4.o

PROGRAM_1 = s1
$(PROGRAM_1): $(Cpp_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

PROGRAM_2 = s2
$(PROGRAM_2): $(Cpp_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)

PROGRAM_3 = s3
$(PROGRAM_3): $(Cpp_OBJ_3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_3) $(INCLUDES) $(LIBS_ALL)

PROGRAM_4 = s4
$(PROGRAM_4): $(Cpp_OBJ_4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_4) $(INCLUDES) $(LIBS_ALL)

all: s1 s2 s3 s4

s_1:
	make $(PROGRAM_1)
s_2:
	make $(PROGRAM_2)
s_3:
	make $(PROGRAM_3)
s_4:
	make $(PROGRAM_4)

r1:
	./s1.exe sphere0.pgm 110 attr.txt

r2:
	./s2.exe attr.txt sphere1.pgm sphere2.pgm sphere3.pgm dir.txt

r3:
	./s3.exe dir.txt object1.pgm object2.pgm object3.pgm 5 norm.pgm

r4:
	./s4.exe dir.txt object1.pgm object2.pgm object3.pgm alb.pgm

clean:
	(rm -f *.o;)

(:
