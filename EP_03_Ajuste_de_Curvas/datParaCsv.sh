#!/bin/bash

# Caminho para o diretório onde os arquivos .dat estão localizados
	diretorio="dados"  # Altere para o diretório correto

# Encontra todos os arquivos .dat no diretório e renomeia para .csv
for arquivo in "$diretorio"/*.dat; do
    # Verifica se o arquivo realmente existe
    if [ -e "$arquivo" ]; then
        # Renomeia o arquivo de .dat para .csv
        mv "$arquivo" "${arquivo%.dat}.csv"
    fi
done

echo "Renomeação concluída!"
