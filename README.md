# FILE COMPRESSOR

This is a program that utilises the [Huffman Algorithm](https://en.wikipedia.org/wiki/Huffman_coding), to compress a text file.

It handles a binary search tree and chained lists to perform the compression.

The text inputs used on the tests, are located on `arquivos_de_teste` folder.

>Disclaimer 1: The algorithm was made for text files. Other types like `.pdf` and `.png` are accepted but wont compress as much as `.txt`

>Disclaimer 2: Make sure you're using UNIX based files, with `LF` on end of lines, and not DOS based files with `CF-LF`.

>Disclaimer 3: Max size 3.5 GB.

Performance results:
```diff
frase.txt         | 1 line    | 4.0 Kb | Compressed to 4.0 Kb   | (00%)
texto_pequeno.txt | 413 lines | 44 Kb  | Compressed to 24.0 Kb  | (55%)
texto_mediano.txt | 2.6k lines| 96 Kb  | Compressed to 56.0 Kb  | (58%)
biblia.txt        | 32k lines | 3.9 Mb | Compressed to 2.3 Mb   | (59%)

imagem.jpg        |           | 36 Kb  | Compressed to 36 Kb    | (00%)
imagem.png        |           | 8.0 Kb | Compressed to 8.0 Kb   | (00%)
imagem.jpeg       |           | 12 Kb  | Compressed to 12 Kb    | (00%)
```
>Made by [Matheus Schreiber](https://github.com/matheusschreiber) and [Caio Fiorotti](https://github.com/fiorotticaio) on August 7th, 2022.

