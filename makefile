prog: compacta descompacta
	@ ./compacta nome_arquivo.txt
	@ ./descompacta nome_arquivo.comp

# valgrind: edcare
# 	@ valgrind ./edcare 15

# tests: run_test_1 run_test_2 run_test_3 run_test_4 run_test_5 run_test_6

# run_test_1: copy_test_1 edcare
# 	@ valgrind --log-file="./valgrind_logs_por_teste/valgrind_log1.txt" ./edcare 10
# 	@ rm -rf Testes/Teste1/Saida/.DS_Store
# 	@ -diff -i saidas Testes/Teste1/Saida
# 	@ echo "\033[1;31m[tests] \033[mTESTE 1 RODADO! ✅"

# run_test_2: copy_test_2 edcare
# 	@ valgrind --log-file="./valgrind_logs_por_teste/valgrind_log2.txt" ./edcare 4
# 	@ rm -rf Testes/Teste2/Saida/.DS_Store
# 	@ -diff -i saidas Testes/Teste2/Saida
# 	@ echo "\033[1;31m[tests] \033[mTESTE 2 RODADO! ✅"

# run_test_3: copy_test_3 edcare
# 	@ valgrind --log-file="./valgrind_logs_por_teste/valgrind_log3.txt" ./edcare 16
# 	@ rm -rf Testes/Teste3/Saida/.DS_Store
# 	@ -diff -i saidas Testes/Teste3/Saida
# 	@ echo "\033[1;31m[tests] \033[mTESTE 3 RODADO! ✅"

# run_test_4: copy_test_4 edcare
# 	@ valgrind --log-file="./valgrind_logs_por_teste/valgrind_log4.txt" ./edcare 4
# 	@ rm -rf Testes/Teste4/Saida/.DS_Store
# 	@ -diff -i saidas Testes/Teste4/Saida
# 	@ echo "\033[1;31m[tests] \033[mTESTE 4 RODADO! ✅"

# run_test_5: copy_test_5 edcare
# 	@ valgrind --log-file="./valgrind_logs_por_teste/valgrind_log5.txt" ./edcare 4
# 	@ rm -rf Testes/Teste5/Saida/.DS_Store
# 	@ -diff -i saidas Testes/Teste5/Saida
# 	@ echo "\033[1;31m[tests] \033[mTESTE 5 RODADO! ✅"

# run_test_6: copy_test_6 edcare
# 	@ valgrind --log-file="./valgrind_logs_por_teste/valgrind_log6.txt" ./edcare 15
# 	@ rm -rf Testes/Teste6/Saida/.DS_Store
# 	@ -diff -i saidas Testes/Teste6/Saida
# 	@ echo "\033[1;31m[tests] \033[mTESTE 6 RODADO! ✅"

# copy_test_1:
# 	@ rm -rf entradas/*.txt 
# 	@ rm -rf saidas/*.txt 
# 	@ cp -r Testes/Teste1/Entrada/*.txt entradas/

# copy_test_2:
# 	@ rm -rf entradas/*.txt 
# 	@ rm -rf saidas/*.txt 
# 	@ cp -r Testes/Teste2/Entrada/*.txt entradas/

# copy_test_3:
# 	@ rm -rf entradas/*.txt 
# 	@ rm -rf saidas/*.txt 
# 	@ cp -r Testes/Teste3/Entrada/*.txt entradas/

# copy_test_4:
# 	@ rm -rf entradas/*.txt 
# 	@ rm -rf saidas/*.txt 
# 	@ cp -r Testes/Teste4/Entrada/*.txt entradas/

# copy_test_5:
# 	@ rm -rf entradas/*.txt 
# 	@ rm -rf saidas/*.txt 
# 	@ cp -r Testes/Teste5/Entrada/*.txt entradas/

# copy_test_6:
# 	@ rm -rf entradas/*.txt 
# 	@ rm -rf saidas/*.txt 
# 	@ cp -r Testes/Teste6/Entrada/*.txt entradas/

compacta: 
	@ gcc -o compacta *.o main.c -lm
	@ echo "\033[1;32m[construtor] \033[mArquivo compacta gerado com sucesso! ✅"

descompacta: 
	@ gcc -o descompacta *.o main.c -lm
	@ echo "\033[1;32m[construtor] \033[mArquivo descompacta gerado com sucesso! ✅"

# idoso: 
# 	@ gcc -c implementacoes/Idoso.c 
	
# 	@ echo "\033[1;32m[construtor] \033[mIdoso.c compilado ✅"

# cuidador:
# 	@ gcc -c implementacoes/Cuidador.c
# 	@ echo "\033[1;32m[construtor] \033[mCuidador.c compilado ✅"

# listas:
# 	@ gcc -c implementacoes/Lista_I.c
# 	@ echo "\033[1;32m[construtor] \033[mLista_I.c compilado ✅"

# 	@ gcc -c implementacoes/Lista_C.c
# 	@ echo "\033[1;32m[construtor] \033[mLista_C.c compilado ✅"

clear:
	@ echo "Limpando arquivos..."
	@ rm -f *.o compacta descompacta
#	@ rm -f saidas/*.txt
	@ echo "Limpo!"