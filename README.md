# Restaurante-RU

Trabalho 1 de Sistemas Operacionais - Restaurante RU usando semáforo e memoria compartilhada.

## Informações

Este trabalho tem como objetivo utilizar processos em paralelo usando memoria compartilhada e semáforos;
- Ao executar o programa, o usuário deve inserir como parametro do estudante o seu nome e do cozinheiro a quantidade de porções
- O programa pode ser iniciado de ambos os lados __estudante/cozinheiro__

## Compilação
- necessario ter um compilador de C++ instalado (GCC ou Clang)
    - executar pelo terminal do windows\linux 
    - ir até o diretorio do codigo fonte e digitar

Para o Estudante:
<pre>
    g++ .\estudante.cpp -o .\estudante && .\estudante (NomeEstudante)
    ou
    clang++ .\estudante.cpp -o .\estudante && .\estudante (NomeEstudante)
</pre>

Para o Cozinheiro:
<pre>
    g++ .\cozinheiro.cpp -o .\cozinheiro && .\cozinheiro (NumeroDePorcoes)
    ou
    clang++ .\cozinheiro.cpp -o .\cozinheiro && .\cozinheiro (NumeroDePorcoes)
</pre>

- Uma alternativa mais simples é utilizar o Visual Studio/VSCode/CodeBlocks ou qualquer outra IDE com C++ configurado. 
- __Obs__: Nerd Fonts talvez necessario para apresentação de caracteres especiais.

### Demonstração

A seguir dois print do programa compilado e executado com 1 cozinheiro e 4 estudantes:

<img src = "https://github.com/eriklemy/Restaurante-RU/blob/main/Restaurante_RU_01.png">

<img src = "https://github.com/eriklemy/Restaurante-RU/blob/main/Restaurante_RU_02.png">
