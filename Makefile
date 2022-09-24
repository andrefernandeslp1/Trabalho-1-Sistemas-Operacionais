app: clean main comp exec

clean:
	rm -f matrizes_threads/*.txt

main: 

	mkdir -p matrizes_threads

comp: 
	gcc auxiliar.c -o auxiliar
	gcc sequencial.c -o sequencial
	gcc paralelo_threads.c -o paralelo_threads -pthread

exec: 
	./auxiliar 100 100 100 100
	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 5