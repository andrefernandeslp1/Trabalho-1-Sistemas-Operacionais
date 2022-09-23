app: msg mkdir_threads comp run

msg:
	@echo Compilando...

mkdir_threads:
	mkdir matrizes_threads

comp:
	gcc auxiliar.c -o auxiliar
	gcc sequencial.c -o sequencial
	gcc paralelo_threads_3.c -o paralelo_threads -pthread
	
run:
	./auxiliar 10 10 10 10
	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 5

reload: app