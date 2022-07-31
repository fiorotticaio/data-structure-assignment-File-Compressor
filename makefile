all: prog verificador

prog: clear compacta descompacta
	@ ./compacta teste.txt
	@ ./descompacta teste.comp

verificador: prog
	@ echo "\033[1;36m\n\n[verificador] \033[mTamanho dos arquivos:"
	@ du -h teste.comp && du -h teste.txt

	@ echo "\033[1;36m\n[verificador] \033[mDiff entre os arquivos:"
	@ diff teste.txt teste_saida.txt
	@ echo "---\n"

valgrind: clear compacta descompacta
	@ valgrind ./compacta teste.txt
	@ valgrind ./descompacta teste.comp

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