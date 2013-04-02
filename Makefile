all:
	g++ -o hypno *.cpp -lX11 -lglut -lGL -lGLU -lm 

clean-all:
	rm -f *~ hypno