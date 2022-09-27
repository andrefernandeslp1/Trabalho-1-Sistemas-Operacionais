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
	gcc leitura_dados.c -o leitura_dados

exec: 
	@echo Executando...
	./auxiliar 2400 2400 2400 2400
	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 2

	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 3

	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 4

	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 5

	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 6

	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 7

	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 8

	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 9

	./sequencial matriz_1.txt matriz_2.txt
	./paralelo_threads matriz_1.txt matriz_2.txt 720000
	./paralelo_processos matriz_1.txt matriz_2.txt 720000
	./leitura_dados 8 10