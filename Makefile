#E1
e1: main clean comp exec

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
	gcc paralelo_threads.c -o paralelo_threads -pthread -lm
	gcc paralelo_processos.c -o paralelo_processos -lm
	gcc leitura_dados_E1.c -o leitura_dados_E1

exec: 
	@echo Executando E1...
	for num in 300 ; do \
			./auxiliar $$num $$num $$num $$num ; \
		echo P = \[ n1xm2 / 8 \] ; \
		for i in `seq 1 1` ; do \
			num2=$$(( (num*num)/8 )) ; \
			echo SEQUENCIAL $$num x $$num Execucao $$i ; \
			./sequencial matriz_1.txt matriz_2.txt ; \
			echo THREADS $$num x $$num Execucao $$i ;  \
			./paralelo_threads matriz_1.txt matriz_2.txt $$num2 ; \
			echo PROCESSOS $$num x $$num Execucao $$i ; \
			./paralelo_processos matriz_1.txt matriz_2.txt $$num2 ; \
			echo LEITURA $$num x $$num Execucao $$i ; \
			./leitura_dados_E1 8 $$i ; \
		done ; \
	done

#E2
e2: main_e2 comp_e2 exec_e2

main_e2: 
	@echo Criando patas, se nao existentes...
	mkdir -p matrizes_threads
	mkdir -p matrizes_processos

comp_e2: 
	@echo Compilando...
	gcc auxiliar.c -o auxiliar
	gcc sequencial.c -o sequencial
	gcc paralelo_threads.c -o paralelo_threads -pthread
	gcc paralelo_processos.c -o paralelo_processos
	gcc cria_arquivo_resultados_E2.c -o cria_arquivo_resultados_E2
	gcc leitura_dados_E2.c -o leitura_dados_E2

exec_e2:
	@echo Executando E2...
	dim=1200 ; \
		./auxiliar $$dim $$dim $$dim $$dim ; \
		./sequencial matriz_1.txt matriz_2.txt ; \
		./cria_arquivo_resultados_E2 ; \
	P=0 ; \
	for i in 32 16 8 4 2 ; do \
		P=$$(( (dim*dim)/i )) ; \
		for j in `seq 1 3` ; do \
			#echo P = $$P ; \
			#echo Limpando pastas... ; \
			rm -f matrizes_threads/*.txt ; \
			rm -f matrizes_processos/*.txt ; \
			./paralelo_threads matriz_1.txt matriz_2.txt $$P ; \
			./paralelo_processos matriz_1.txt matriz_2.txt $$P ; \
			./leitura_dados_E2 $$i ; \
		done ; \
	done