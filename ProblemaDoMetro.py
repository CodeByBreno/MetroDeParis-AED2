import tkinter as tk
import pandas as pd

# Dicionário fornecido
distances = {
    "E1": {
        "E2": 10,
        "E3": 18.5,
        "E4": 24.8,
        "E5": 36.4,
        "E6": 38.8,
        "E7": 35.8,
        "E8": 25.4,
        "E9": 17.6,
        "E10": 9.1,
        "E11": 16.7,
        "E12": 27.3,
        "E13": 27.6,
        "E14": 29.8,
    },
    "E2": {
        "E3": 8.5,
        "E4": 14.8,
        "E5": 26.6,
        "E6": 29.1,
        "E7": 26.1,
        "E8": 17.3,
        "E9": 10,
        "E10": 3.5,
        "E11": 15.5,
        "E12": 20.9,
        "E13": 19.1,
        "E14": 21.8,
    },
    "E3": {
        "E4": 6.3,
        "E5": 18.2,
        "E6": 20.6,
        "E7": 17.6,
        "E8": 13.6,
        "E9": 9.4,
        "E10": 10.3,
        "E11": 19.5,
        "E12": 19.1,
        "E13": 12.1,
        "E14": 16.6,
    },
    "E4": {
        "E5": 12,
        "E6": 14.4,
        "E7": 11.5,
        "E8": 12.4,
        "E9": 12.6,
        "E10": 16.7,
        "E11": 23.6,
        "E12": 18.6,
        "E13": 10.6,
        "E14": 15.4,
    },
    "E5": {
        "E6": 3,
        "E7": 2.4,
        "E8": 19.4,
        "E9": 23.3,
        "E10": 28.2,
        "E11": 34.2,
        "E12": 24.8,
        "E13": 14.5,
        "E14": 17.9,
    },
    "E6": {
        "E7": 3.3,
        "E8": 22.3,
        "E9": 25.7,
        "E10": 30.3,
        "E11": 36.7,
        "E12": 27.6,
        "E13": 15.2,
        "E14": 18.2,
    },
    "E7": {
        "E8": 20,
        "E9": 23,
        "E10": 27.3,
        "E11": 34.2,
        "E12": 25.7,
        "E13": 12.4,
        "E14": 15.6,
    },
    "E8": {"E9": 8.2, "E10": 20.3, "E11": 16.1, "E12": 6.4, "E13": 22.7, "E14": 27.6},
    "E9": {"E10": 13.5, "E11": 11.2, "E12": 10.9, "E13": 21.2, "E14": 26.6},
    "E10": {"E11": 17.6, "E12": 24.2, "E13": 18.7, "E14": 21.2},
    "E11": {"E12": 14.2, "E13": 31.5, "E14": 35.5},
    "E12": {"E13": 28.8, "E14": 33.6},
    "E13": {"E14": 5.1},
}

# Lista de cidades
cities = [f"E{i}" for i in range(1, 15)]

# Inicializa a tabela com zeros
table = {city: {city: 0 for city in cities} for city in cities}

# Preenche a tabela com as distâncias do dicionário
for city, connections in distances.items():
    for connected_city, distance in connections.items():
        table[city][connected_city] = distance
        table[connected_city][city] = distance  # A distância é simétrica

# Converte a tabela para um DataFrame do pandas
df = pd.DataFrame(table)

# Função para criar a interface Tkinter
def create_table_interface(dataframe):
    root = tk.Tk()
    root.title("Tabela de Distâncias")

    # Cria o frame para a tabela
    frame = tk.Frame(root)
    frame.pack()

    # Adiciona os cabeçalhos
    for j, city in enumerate([""] + dataframe.columns.tolist()):
        label = tk.Label(frame, text=city, borderwidth=1, relief="solid")
        label.grid(row=0, column=j, sticky="nsew")

    # Adiciona os dados da tabela
    for i, city in enumerate(dataframe.index):
        label = tk.Label(frame, text=city, borderwidth=1, relief="solid")
        label.grid(row=i + 1, column=0, sticky="nsew")
        for j, value in enumerate(dataframe.loc[city]):
            label = tk.Label(frame, text=value, borderwidth=1, relief="solid")
            label.grid(row=i + 1, column=j + 1, sticky="nsew")

    # Configura o layout para redimensionamento
    for i in range(len(dataframe.index) + 1):
        frame.grid_rowconfigure(i, weight=1)
    for j in range(len(dataframe.columns) + 1):
        frame.grid_columnconfigure(j, weight=1)

    root.mainloop()

# Cria a interface com a tabela de distâncias
create_table_interface(df)
