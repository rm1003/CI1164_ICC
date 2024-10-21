#########################################
#   Ruibin Mei							#
#   GRR20232358							#
#										#
#   Script para Likwid					#
#########################################

#!/bin/bash

# Cria um arquivo temporario para armazenar a saida do likwid-perfctr
TEMP_OUTPUT=$(mktemp)

# Executa o likwid-perfctr para medir FLOPS_DP no núcleo 0
# O programa e ./inversa e a saida e redirecionada para o arquivo temporario
likwid-perfctr -C 0 -g FLOPS_DP -m ./inversa > "$TEMP_OUTPUT"

# Exibe as linhas entre /inicio e /fim, removendo essas tags de marcação
# Usa awk para pegar o intervalo entre /inicio e /fim e remove as próprias tags com sed
cat "$TEMP_OUTPUT" | awk '/\/inicio/,/\/fim/' | sed '/\/inicio/d' | sed '/\/fim/d'

# Adiciona uma linha em branco
echo

# Filtra as métricas relevantes da saída:
# - FP_ARITH_INST_RETIRED_SCALAR_DOUBLE
# - DP MFLOP/s
# Exclui quaisquer referências ao conjunto de instruções AVX usando 'grep -v "AVX"'
cat "$TEMP_OUTPUT" | grep -E "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE|DP MFLOP/s" | grep -v "AVX"

# Remove o arquivo temporário
rm "$TEMP_OUTPUT"
