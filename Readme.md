# Algoritmos Construtivos para o Problema da Árvore Geradora Minima com Restrição de Grau 

## Grupo 10:
- André Dias
- Jean Felipe Henriques Coutinho
- Yuri Clemente Moreira
## Descriçao

Resolução de problemas que envolvem Árvore Geradora Minima com Restrição de Grau utilizando os algoritimos:
- Guloso
- Guloso Randomizado
- Guloso Randomizado Reativo

## Como compilar

Comando para compilação:  

  g++ *.cpp *.h -o ExecGrupo10 -O3 

## Como Executar

Comando para execução: 

  ./main <"caminho/instancia.tsp"> <"caminho/ParaSaida/Resultados">

O caminho de saida para os resultados não deve incluir "/" ao final.

## Input

### Digite 1 para a execução do algoritimo guloso.

### Digite 2 para a execução do algoritmo guloso randomizado.
  - Inserir a quantidade de iterações desejadas.
  - Inserir um valor para ser usado de seed.

### Digite 3 para a execução do algoritmo guloso randomizado reativo.
  - Inserir a quantidade de iterações desejadas.
  - Inserir tamanho do bloco desejado (Quantidade de iterações ate que seja realizada o recalculo de probabilidades).
  - Inserir um valor para ser usado de seed.

## Output
### Execução do algoritimo Guloso:
  - Via console: Resultados contendo Tempo de execução e valor da solução. 
  - Saida ResultadoGuloso.txt em formato de tabela (separadas por ";") no formato: "Instancia;Solucao;Tempos(s)"

### Execução do algoritimo Guloso Randomizado:
  - Via console: Resultados contendo Tempo Medio, para cada um dos 5 alfas (0,05;0,1;0,15;0,3;0,5) e seus respectivos melhores soluções. 
  - Saida ResultadoRandomizado.txt em formato de tabela no formato: "Instancia;Alfa0,05;Tempos(s);Alfa0,1;Tempos(s);Alfa0,15;Tempos(s);Alfa0,3;Tempos(s);Alfa0,5;Tempos(s);QuantidadeIterações".

### Execução do algoritimo Guloso Randomizado Reativo:
  - Via console: Resultados contendo Tempo de execução, e valor da melhor solução encontrada.
  - Saida ResultadoRandomizado.txt em formato de tabela no formato: "Instancia;Melhor Solucao;Tempo(s);Quantidade de Iterações;Tamanho do Bloco".