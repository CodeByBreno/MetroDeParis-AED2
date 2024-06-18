# 🗺️ Cálculo de Rotas do Metro de Paris
Esse projeto foi desenvolvido para a disciplina de Algoritmo e Estrutura de Dados 2, em equipe, junto à Alan Victor de Souza Pinho, 
Breno Gabriel de Souza Coelho (eu), Daniel Alencar Penha Carvalho, Mateus Junior de Macedo Cavalcanti, Maic de Oliveira Santo e David Rios.
Foi produzido no semestre 2023.2, como segundo projeto para disciplina antes mencionada, ministrada pela professora Ana Emília.

O objetivo é, se baseando em um conjunto de especificações do projeto presente no arquivo "ProjetoGrafos.pdf", construir um código
que utiliza o Algoritmo A* para buscar o caminho mais rápido entre duas estações de metro de Paris, com base num conjunto de conexões
e linhas especificadas no guia.

Esse programa foi implementado utilizando um código em C, que realiza o algoritmo e descobre o caminho mais rápido entre duas estações,
e um outro código em Python, que utiliza a biblioteca PyGame para implementar uma interface visual que apresenta em tela o resultado da
execução do código em C. Desse modo, o código em Python chama o .exe do arquivo C compilado, passando as estações inicial e final, nos
argv[] via prompt, e o resultado apresentado na stdout é capturado pelo python e usado para construir o visual.

<h2><Strong>Interface do Metro de Paris: </Strong></Strong></h2>
<p align="center">
  <img src="https://github.com/CodeByBreno/MetroDeParis-AED2/assets/132024181/ffbacc3a-45f4-4d92-b771-2157d56e056b" width="800" alt="analise_algoritmos_ordenacao">
</p>

# ⚙️ Como Executar o Projeto?

O projeto possui duas pastas principais: /Algoritmos e /Interface. Na pasta /Algoritmos se encontram os arquivos em C que realizam o cálculo das rotas, enquanto na
pasta /Interface se encontram os arquivos em Python que implementam a interface visual. 

Para executar o projeto, é muito simples. Basta ter o Python instalado na sua versão mais recente e executar:

<strong>python ./Interface/metro.py</strong>

Caso ocorra algum erro (principalmente se ao executar o código python a interface "travar"), vá na pasta /Algoritmo e compile o arquivo main.cpp novamente. Porém 
isso provavelmente não deve ocorrer. Apenas para contextualizar, o arquivo python está executando o arquivo output/main.exe.

<strong>OBSERVAÇÃO:</strong>
Talvez pareça um erro que algumas estações "conectadas" na ilustração não tenham uma rota conectando-as. A questão é que, se baseando na guia do projeto, nem sempre
existe um caminho entre estações conectadas. Isso ocorre porque a rota pode ser de via única, ou seja, há caminho de E1 para E14, porém não há caminho de E14 para E1.

# 🖼️ Ilustrações do Projeto

<h2><Strong>Interface com um caminho destacado: </Strong></h2>
<p align="center">
  <img src="https://github.com/CodeByBreno/MetroDeParis-AED2/assets/132024181/ed06695a-be9b-4654-867d-fede7cb19990" width="800" alt="analise_algoritmos_ordenacao">
</p>

<h2><Strong>Outro exemplo de interface com um caminho destacado: </Strong></h2>
<p align="center">
  <img src="https://github.com/CodeByBreno/MetroDeParis-AED2/assets/132024181/d894156e-0bd3-4956-9d11-2682e6bfd771" width="800" alt="analise_algoritmos_ordenacao">
</p>

<h2><Strong>Exemplo de um caso onde não há rota conectando as estações: </Strong></h2>
<p align="center">
  <img src="https://github.com/CodeByBreno/MetroDeParis-AED2/assets/132024181/ad0318fd-d331-4f5e-9a25-d43867e7ead1" width="800" alt="analise_algoritmos_ordenacao">
</p>

<h2><Strong>Exemplo de um caso onde tem ida, mas não tem volta: </Strong></h2>
<p align="center">
  <img src="https://github.com/CodeByBreno/MetroDeParis-AED2/assets/132024181/abbd4988-39a6-4626-a5ff-ba0822864c86" width="800" alt="analise_algoritmos_ordenacao">
</p>
<p align="center">
  <img src="https://github.com/CodeByBreno/MetroDeParis-AED2/assets/132024181/5fe7d76c-a008-469b-ae91-b8186cf708fd" width="800" alt="analise_algoritmos_ordenacao">
</p>
