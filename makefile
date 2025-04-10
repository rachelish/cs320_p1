# Specifiy the target
all: predictors
# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
predictors: predictors.o 
	g++ -g predictors.o -o predictors

predictors.o: predictors.cpp
	g++ -c predictors.cpp
# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o predictors
