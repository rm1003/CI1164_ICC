import pandas as pd
import csv
import re
import numpy as np
import matplotlib.pyplot as plt

basedir = "dados/infoSeparado/"
graficos_dir = "graficos/"

funcoes = ["montaSL", "resolveSL"]
versoes = ["v1", "v2"]
graus = [10, 1000]
kpontos = [64, 128, 200, 256, 512, 600, 800, 1024, 2000, 3000, 4096, 6000, 7000, 10000, 50000, 100000]
metricas = ["L3CACHE", "ENERGY", "FLOPS_DP"]
submetricas = ["l3 miss RATIO", "Energy [J]", "DP MFLOP/s"]
colors = ["r", "g", "b", "k", "m", "c"]

# Funções Auxiliares
def find_tag_value(file_path, tag):
    with open(file_path, mode='r') as file:
        reader = csv.reader(file)
        occurrences = [row for row in reader if row and row[0].strip().startswith(tag)]
        return occurrences[:2] if len(occurrences) >= 2 else None

# Gerar dados para os arquivos CSV
for v in versoes:
    for grau in graus:
        montaSL, resolveSL = {m: [] for m in metricas}, {m: [] for m in metricas}

        for m in metricas:
            for pontos in kpontos:
                metric = "L3 miss ratio" if m == "L3CACHE" else "Energy [J]" if m == "ENERGY" else "DP MFLOP/s"
                dados = find_tag_value(f"dados/{v}-{grau}-{pontos}-{m}.csv", metric)
                if dados:
                    montaSL[m].append(dados[0][1])
                    resolveSL[m].append(dados[1][1])

        pd.DataFrame(montaSL).to_csv(f"{basedir}{v}-{grau}-montaSL.csv", index=False)
        pd.DataFrame(resolveSL).to_csv(f"{basedir}{v}-{grau}-resolveSL.csv", index=False)

# Gerar gráficos para métricas
for a, m in enumerate(metricas):
    for funcao in funcoes:
        for k, v in enumerate(versoes):
            for j, grau in enumerate(graus):
                data = np.genfromtxt(f"{basedir}{v}-{grau}-montaSL.csv", delimiter=',', skip_header=1)
                y_values = data[:, a]
                plt.plot(kpontos, y_values, marker='o', linestyle='-', color=colors[(j + k) % len(colors)], label=f"{v} {grau}")
        plt.xscale('log')  # Escala logarítmica no eixo x
        plt.yscale('log')  # Escala logarítmica no eixo y
        plt.xlabel('kPontos')
        plt.ylabel(submetricas[a])
        plt.title(f"{m} {funcao}")
        plt.legend()
        plt.grid(True)
        plt.savefig(f"{graficos_dir}{funcao}-{m}.png")
        plt.clf()

# Função para gerar gráficos de tempo
def plot_tempo_graficos_combinados(arquivo_v1, arquivo_v2):
    try:
        def carregar_tempos(arquivo):
            data = np.genfromtxt(arquivo, delimiter=',', skip_header=1)
            return {
                "montaSL": data[::2, 1][:len(kpontos)],
                "solucaoSL": data[::2, 2][:len(kpontos)],
                "montaSL_likwid": data[1::2, 1][:len(kpontos)],
                "solucaoSL_likwid": data[1::2, 2][:len(kpontos)]
            }

        tempos_v1 = carregar_tempos(arquivo_v1)
        tempos_v2 = carregar_tempos(arquivo_v2)

        def plotar(nome, tempos_v1, tempos_v2):
            plt.plot(kpontos, tempos_v1["montaSL"], 'o-r', label="v1 - Padrão")
            plt.plot(kpontos, tempos_v1["montaSL_likwid"], 'o-g', label="v1 - Likwid")
            plt.plot(kpontos, tempos_v2["montaSL"], 'x-b', label="v2 - Padrão")
            plt.plot(kpontos, tempos_v2["montaSL_likwid"], 'x-m', label="v2 - Likwid")
            plt.xscale('log')  # Escala logarítmica no eixo x
            plt.yscale('log')  # Escala logarítmica no eixo y
            plt.xlabel("kPontos")
            plt.ylabel("Tempo (ms)")
            plt.title(f"Comparação de Tempo - {nome}")
            plt.legend()
            plt.grid(True)
            plt.savefig(f"{graficos_dir}comparacao_{nome}.png")
            plt.clf()

        plotar("montaSL", tempos_v1, tempos_v2)
        plotar("solucaoSL", 
               {"montaSL": tempos_v1["solucaoSL"], "montaSL_likwid": tempos_v1["solucaoSL_likwid"]},
               {"montaSL": tempos_v2["solucaoSL"], "montaSL_likwid": tempos_v2["solucaoSL_likwid"]})

    except Exception as e:
        print(f"Erro ao gerar gráficos combinados: {e}")

# Gerar gráficos de tempo
plot_tempo_graficos_combinados("dados/v1-tempo.csv", "dados/v2-tempo.csv")
