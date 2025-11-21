import matplotlib.pyplot as plt
import numpy as np

# ===============================
# 1. Entrada de dados pelo usuário
# ===============================
print("=== COLETA DE DADOS ===")
quantidade = int(input("Quantos alunos deseja cadastrar? "))

nomes = []
idades = []
notas = []

for i in range(quantidade):
    print(f"\nAluno {i+1}:")
    nome = input("  Nome: ")
    idade = int(input("  Idade: "))
    nota = float(input("  Nota (0 a 10): "))

    nomes.append(nome)
    idades.append(idade)
    notas.append(nota)

# ===============================
# 2. Preparação dos dados
# ===============================
idades = np.array(idades)
notas = np.array(notas)

# Tamanho e cor dos pontos de acordo com a nota
tamanhos = (notas + 1) * 30
cores = notas

# ===============================
# 3. Criação do gráfico
# ===============================
plt.figure(figsize=(15, 9))
scatter = plt.scatter(
    idades,
    notas,
    s=tamanhos,
    c=cores,
    cmap='plasma',
    alpha=0.8,
    edgecolors='k'
)

# Títulos e rótulos
plt.title("Relação entre Idade e Nota — Gráfico de Pontos", fontsize=14, pad=15)
plt.xlabel("Idade (anos)", fontsize=12)
plt.ylabel("Nota obtida", fontsize=12)
plt.grid(True, linestyle="--", alpha=0.2)

# Barra de cores
cbar = plt.colorbar(scatter)
cbar.set_label("Desempenho (nota)", fontsize=11)

# Linhas médias
media_nota = float(np.mean(notas))
plt.axhline(media_nota, color='gray', linestyle='--', linewidth=1, label=f"Média Nota: {media_nota:.2f}")

media_idade = int(round(np.mean(idades)))
plt.axvline(media_idade, color='gray', linestyle=':', linewidth=1, label=f"Média Idade: {media_idade}")

# ===============================
# 4. Anotações dos pontos
# ===============================
for i in range(quantidade):
    plt.text(idades[i], notas[i], nomes[i], fontsize=8, color='black')

plt.legend(loc="lower right")
plt.tight_layout()

# ===============================
# 5. Salvando o gráfico em SVG
# ===============================
arquivo_svg = "grafico_pontos_alunos.svg"
plt.savefig(arquivo_svg, format="svg")
plt.close()

print("\n✅ Gráfico criado e salvo com sucesso!")
print(f"Arquivo gerado: {arquivo_svg}")

# ===============================
# 6. Resumo (para o relatório escolar)
# ===============================
print("\n=== RESUMO ===")
print(f"Número de alunos: {quantidade}")
print(f"Média das idades: {np.mean(idades):.2f} anos")
print(f"Média das notas: {np.mean(notas):.2f}")
print(f"Maior nota: {np.max(notas):.2f} ({nomes[np.argmax(notas)]})")
print(f"Menor nota: {np.min(notas):.2f} ({nomes[np.argmin(notas)]})")
print("\nO gráfico foi salvo em formato SVG e pode ser aberto em qualquer navegador.")
