all:
	g++ -o hypno *.cpp -lX11 -lXmu -lglut -lGL -lGLU -lm 

clean-all:
	rm -f *~ hypno