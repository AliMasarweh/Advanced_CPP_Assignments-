CXX=g++
CXXFLAGS = -std=c++11

all: Editor.o Document.o 
	$(CXX) $(CXXFLAGS) Editor.o Document.o
	./a.out

Editor.o: Editor.cpp Editor.h Document.h
	$(CXX) $(CXXFLAGS) -c Editor.cpp

Document.o: Document.cpp Document.h
	$(CXX) $(CXXFLAGS) -c Document.cpp

clean:
	rm *.o a.out