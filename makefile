name = teste
file = txt

all: prog warning verificador 

prog: clear compacta descompacta
	@ ./compacta $(name).$(file)
	@ ./descompacta $(name).comp

warning:
	@ echo "\033[1;93m\n[warning] \033[mTamanho máximo permitido: 3.5 gb (long int)"

verificador: prog
	@ echo "\033[1;36m\n[verificador] \033[mTamanho dos arquivos:"
	@ du -h $(name).comp && du -h $(name).$(file) && du -h $(name)_saida.$(file)

	@ echo "\033[1;36m\n[verificador] \033[mDiff entre os arquivos:"
	@ -diff $(name).$(file) $(name)_saida.$(file)
	@ echo "---\n"

val: clear compacta descompacta
	@ valgrind ./compacta $(name).$(file)
	@ valgrind ./descompacta $(name).comp

Arvore_bin:
	@ gcc -c ./implementacoes/Arvore_bin.c -lm
	@ echo "\033[1;32m[compilador] \033[mArquivo 'Arvore_bin' compilado com sucesso! ✅"

Lista_arv:
	@ gcc -c ./implementacoes/Lista_arv.c -lm
	@ echo "\033[1;32m[compilador] \033[mArquivo 'Lista_arv' compilado com sucesso! ✅"

bitmap:
	@ gcc -c ./implementacoes/bitmap.c -lm
	@ echo "\033[1;32m[compilador] \033[mArquivo 'bitmap' compilado com sucesso! ✅"

compacta: bitmap Arvore_bin Lista_arv
	@ gcc -o compacta *.o compacta.c -lm
	@ echo "\033[1;32m[compilador] \033[mArquivo 'compacta' gerado com sucesso! ✅"

descompacta: Arvore_bin Lista_arv
	@ gcc -o descompacta *.o descompacta.c -lm
	@ echo "\033[1;32m[compilador] \033[mArquivo 'descompacta' gerado com sucesso! ✅"

clear:
	@ rm -f *.o compacta descompacta
	@ echo "\033[1;34m[limpador] \033[mDiretório Limpo! ✅\n"