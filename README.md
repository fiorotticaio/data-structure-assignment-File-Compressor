# File Compressor

PDF:
https://docs.google.com/document/d/1lVG9BgJnDPhR-pshuRK7jyqfclTDOxCmTPYO8vjrtjs/edit?usp=sharing

## Etapas e TODO's

    [ ] Usar um menor número de bits para caracteres que aparecem mais vezes
    
    [ ] implementando com árvore binária que armazena caracteres nas folhas

    [ ] caminhos da raiz até a folha que provém a sequência de bits de cada caractere
        
        [ ] sub-árvore da direita: 1

        [ ] sub-árvore da esquerda: 0

    [ ] o número de vezes que o caractere aparece é seu peso

    [x] primeiro passo: fazer o TAD arvore_bin

	    [x] a info vai ser um caracter

    	[x] o peso vai ser o número de ocorrências de cada caracter (adquirido daquele vetor)
	
    [x] segundo passo: fazer o TAD lista de árvores

        [x] lista encadeada

        [x] função de ordenar

        [x] função de Huffman

    [x] Usar Graphviz online para fazer os diagramas das árvores

    [ ] Verificar documentação dos cabeçalhos (.h)
