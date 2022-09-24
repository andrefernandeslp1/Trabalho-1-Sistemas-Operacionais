app: main clean comp exec

main: 
	@echo Criando diretorios, se nao existentes...
	mkdir -p matrizes_threads

clean:
	@echo Limpando pastas...
	rm -f matrizes_threads/*.txt

comp: 
	@echo Compilando...
	gcc auxiliar.c -o auxiliar
	gcc sequencial.c -o sequencial
	gcc paralelo_threads.c -o paralelo_threads -pthread

exec: 
	@echo Executando...
	./auxiliar 5 10 10 5
	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 5