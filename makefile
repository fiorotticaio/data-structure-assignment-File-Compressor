prog: clear compacta 
	@ ./compacta teste.txt
#	@ ./descompacta teste.comp

valgrind: clear compacta
	@ valgrind ./compacta teste.txt

Arvore_bin:
	@ gcc -c ./implementacoes/Arvore_bin.c -lm
	@ echo "\033[1;32m[makefile] \033[mArquivo 'Arvore_bin' compilado com sucesso! ✅"

Lista_arv:
	@ gcc -c ./implementacoes/Lista_arv.c -lm
	@ echo "\033[1;32m[makefile] \033[mArquivo 'Lista_arv' compilado com sucesso! ✅"

bitmap:
	@ gcc -c ./implementacoes/bitmap.c -lm
	@ echo "\033[1;32m[makefile] \033[mArquivo 'bitmap' compilado com sucesso! ✅"

compacta: bitmap Arvore_bin Lista_arv
	@ gcc -o compacta *.o compacta.c -lm
	@ echo "\033[1;32m[makefile] \033[mArquivo 'compacta' gerado com sucesso! ✅"

descompacta: Arvore_bin Lista_arv
	@ gcc -o descompacta *.o descompacta.c -lm
	@ echo "\033[1;32m[makefile] \033[mArquivo 'descompacta' gerado com sucesso! ✅"

clear:
	@ rm -f *.o compacta descompacta
#	@ rm -f saidas/*.txt
	@ echo "\033[1;32m[makefile] \033[mDiretório Limpo! ✅"