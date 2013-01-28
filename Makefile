all:
	g++ -o hypno *.cpp  -I/usr/local/glut/include -L/usr/local/glut/lib/glut -L/usr/openwin/lib -lX11 -lXmu -lglut -lGL -lGLU -lm 

clean-all:
	rm -f *~ hypno