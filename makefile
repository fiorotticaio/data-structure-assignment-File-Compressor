name = imagem
file = jpeg

all: prog warning verificador 

hex: prog
	@ echo "\033[1;93m\n[hexdump] \033[mConteudo em hexadecimal do arquivo compactado"
	@ echo "\033[1;93m|\033[m n° de linhas \033[1;93m|\033[m conteudo \033[1;93m|\033[m conteudo convertido em %_p\n"
	@ hexdump -C $(name).comp

prog: clear compacta descompacta
	@ ./compacta.out $(name).$(file)
	@ ./descompacta.out $(name).comp

warning:
	@ echo "\033[1;93m\n[warning] \033[mTamanho máximo permitido: 3.5 gb (long int)"

verificador: prog
	@ echo "\033[1;36m\n[verificador] \033[mTamanho (aprox) dos arquivos:"
	@ du -h $(name).comp && du -h $(name).$(file) && du -h ./arquivos_de_saida/$(name).$(file)

	@ echo "\033[1;36m\n[verificador] \033[mDiff entre os arquivos:"
	@ -diff $(name).$(file) ./arquivos_de_saida/$(name).$(file)
	@ echo "---\n"

val: clear compacta descompacta
	@ valgrind ./compacta.out $(name).$(file)
	@ valgrind ./descompacta.out $(name).comp

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
	@ gcc -o compacta.out *.o compacta.c -lm
	@ echo "\033[1;32m[executaveis] \033[mArquivo 'compacta.out' gerado com sucesso! ✅"

descompacta: Arvore_bin Lista_arv
	@ gcc -o descompacta.out *.o descompacta.c -lm
	@ echo "\033[1;32m[executaveis] \033[mArquivo 'descompacta.out' gerado com sucesso! ✅"

clear:
	@ rm -f *.o compacta.out descompacta.out *.comp
	@ echo "\033[1;34m[limpador] \033[mDiretório Limpo! ✅\n"