

nladveccions.x:nladveccionserie.c
	gcc nladveccionserie.c -o nladveccions.x  
	./nladveccions.x
	rm *.x
	rm *.txt

nladveccionp.x:nladveccionparalelo.c
	gcc nladveccionparalelo.c -o nladveccionp.x  
	./nladveccionp.x
	rm *.x
	rm *.txt


hello.x:HelloWorld.c
	gcc -fopenmp HelloWorld.c -o hello.x
	./hello.x 
	python plons.py
	rm *.x
