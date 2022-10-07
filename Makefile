#E1
e1: main comp exec

main:
	@echo
	@echo Criando patas, se nao existentes...
	mkdir -p matrizes_threads
	mkdir -p matrizes_processos

comp:
	@echo
	@echo Compilando...
	gcc auxiliar.c -o auxiliar
	gcc sequencial.c -o sequencial
	gcc paralelo_threads.c -o paralelo_threads -pthread -lm
	gcc paralelo_processos.c -o paralelo_processos -lm
	gcc leitura_dados_E1.c -o leitura_dados_E1

exec:
	@echo
	@echo Executando E1...
	@echo
	for num in 150 300 600 1200 2400 ; do \
		./auxiliar $$num $$num $$num $$num ; \
		echo ; \
		for i in `seq 1 10` ; do \
			num2=$$(( (num*num)/8 )) ; \
			echo $$num x $$num - Execucao $$i ; \
			echo P = \[ n1xm2 / 8 \] ; \
			echo Limpando pastas... ; \
			rm -f matrizes_threads/*.txt ; \
			rm -f matrizes_processos/*.txt ; \
			echo Rodando SEQUENCIAL... ; \
			./sequencial matriz_1.txt matriz_2.txt ; \
			echo Rodando THREADS... ;  \
			./paralelo_threads matriz_1.txt matriz_2.txt $$num2 ; \
			echo Rodando PROCESSOS... ; \
			./paralelo_processos matriz_1.txt matriz_2.txt $$num2 ; \
			echo Leitura dos Dados ; \
			./leitura_dados_E1 8 $$i ; \
			echo ; \
		done ; \
	done

#E2
e2: main_e2 comp_e2 exec_e2

main_e2: 
	@echo
	@echo Criando patas, se nao existentes...
	mkdir -p matrizes_threads
	mkdir -p matrizes_processos

comp_e2:
	@echo
	@echo Compilando...
	gcc auxiliar.c -o auxiliar
	gcc sequencial.c -o sequencial
	gcc paralelo_threads.c -o paralelo_threads -pthread -lm
	gcc paralelo_processos.c -o paralelo_processos -lm
	gcc cria_arquivo_resultados_E2.c -o cria_arquivo_resultados_E2
	gcc leitura_dados_E2.c -o leitura_dados_E2

exec_e2:
	@echo
	@echo Executando E2...
	@echo
	echo ; \
	dim=2400 ; \
	echo Gerando Matrizes... ; \
	./auxiliar $$dim $$dim $$dim $$dim ; \
	#./sequencial matriz_1.txt matriz_2.txt ; \
	./cria_arquivo_resultados_E2 ; \
	P=0 ; \
	for i in 32 16 8 4 2 ; do \
		echo ; \
		P=$$(( (dim*dim)/i )) ; \
		for j in `seq 1 10` ; do \
			echo P = \[ n1xm2 / $$i \] ; \
			echo $$dim x $$dim - Execucao $$j ; \
			echo Limpando pastas... ; \
			rm -f matrizes_threads/*.txt ; \
			rm -f matrizes_processos/*.txt ; \
			echo Rodando THREADS... ; \
			./paralelo_threads matriz_1.txt matriz_2.txt $$P ; \
			echo Rodando PROCESSOS... ; \
			./paralelo_processos matriz_1.txt matriz_2.txt $$P ; \
			./leitura_dados_E2 $$i ; \
		done ; \
	done