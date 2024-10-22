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

# Exibe as linhas entre /inicio e /fim, removendo essas tags de marcacao
# Usa awk para pegar o intervalo entre /inicio e /fim e remove as próprias tags com sed
cat "$TEMP_OUTPUT" | awk '/\/marcacao-inicial/,/\/marcacao-final/' | sed '/\/marcacao-inicial/d' | sed '/\/marcacao-final/d'

# Filtra as metricas relevantes da saida:
# - FP_ARITH_INST_RETIRED_SCALAR_DOUBLE -> print $4 para imprimir coluna 4
# - DP MFLOP/s -> print $3 para imprimir coluna 3
# Exclui quaisquer referencias ao conjunto de instrucoes AVX usando 'grep -v "AVX"'
FP=$(grep -E "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE" "$TEMP_OUTPUT"  | grep -v "AVX" | awk -F'|' '{print $4}' | tr -d ' ')
DP=$(grep -E "DP \[MFLOP/s\]" "$TEMP_OUTPUT" | grep -v "AVX" | awk -F'|' '{print $3}' | tr -d ' ')

echo
echo "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE,$FP"
echo "DP [MFLOP/s],$DP"
echo

# Remove o arquivo temporario
rm "$TEMP_OUTPUT"
