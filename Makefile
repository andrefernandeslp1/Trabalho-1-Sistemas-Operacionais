app: main clean comp exec

main: 
	@echo Criando patas, se nao existentes...
	mkdir -p matrizes_threads
	mkdir -p matrizes_processos

clean:
	@echo Limpando pastas...
	rm -f matrizes_threads/*.txt
	rm -f matrizes_processos/*.txt

comp: 
	@echo Compilando...
	gcc auxiliar.c -o auxiliar
	gcc sequencial.c -o sequencial
	gcc paralelo_threads.c -o paralelo_threads -pthread
	gcc paralelo_processos.c -o paralelo_processos

exec: 
	@echo Executando...
	./auxiliar 10 10 10 10
	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 5
	./paralelo_processos matriz_1.txt matriz_2.txt 5