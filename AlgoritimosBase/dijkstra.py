import sys

# Número de vértices
V = 5

def min_distance(dist, spt_set):
    """
    Retorna o índice do vértice com a menor distância atual, que ainda não foi incluído no conjunto de caminhos mínimos.
    """
    min_val = sys.maxsize
    min_index = -1

    for v in range(V):
        if not spt_set[v] and dist[v] < min_val:
            min_val = dist[v]
            min_index = v
    return min_index

def print_solution(dist, src):
    """
    Imprime as distâncias do vértice de origem para todos os outros vértices.
    """
    print(f"Distâncias a partir do vértice {src}:")
    for i in range(V):
        if dist[i] == sys.maxsize:
            print(f"Vértice {i}: sem caminho")
        else:
            print(f"Vértice {i}: {dist[i]}")

def dijkstra(graph, src):
    # dist[i] guardará a menor distância de src até i
    dist = [sys.maxsize] * V
    # spt_set[i] será True se o vértice i já foi incluído no caminho mínimo definido
    spt_set = [False] * V

    # A distância do vértice de origem até ele mesmo é sempre 0
    dist[src] = 0

    for _ in range(V - 1):
        # Escolhe o vértice não visitado com a menor distância atual
        u = min_distance(dist, spt_set)

        # Marca este vértice como processado
        spt_set[u] = True

        # Atualiza as distâncias dos vértices vizinhos
        for v in range(V):
            # Atualiza dist[v] se:
            # 1) Ainda não visitado (spt_set[v] == False)
            # 2) Existe uma aresta de u para v (graph[u][v] != 0)
            # 3) dist[u] não é infinito
            # 4) dist[u] + graph[u][v] < dist[v]
            if (not spt_set[v] and graph[u][v] != 0 and dist[u] != sys.maxsize and dist[u] + graph[u][v] < dist[v]):
                dist[v] = dist[u] + graph[u][v]

    print_solution(dist, src)

# Exemplo de uso
if __name__ == "__main__":
    # 0 indica ausência de aresta direta entre dois vértices diferentes
    graph = [
        [0, 2, 5, 0, 0],
        [2, 0, 1, 4, 0],
        [5, 1, 0, 2, 6],
        [0, 4, 2, 0, 3],
        [0, 0, 6, 3, 0]
    ]

    origem = 0
    dijkstra(graph, origem)
