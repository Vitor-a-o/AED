edges = [
    (2, 'B', 'C'),
    (1, 'A', 'B'),
    (2, 'A', 'C'),
    (3, 'C', 'D'),
    (4, 'B', 'D'),
    (5, 'A', 'D'),
    (6, 'C', 'E'),
    (7, 'D', 'E'),
    (8, 'B', 'E')
]

edges.sort(key=lambda x: x[0])

vertices = set()
for w, u, v in edges:
    vertices.add(u)
    vertices.add(v)
    
parent = {v: v for v in vertices}
rank = {v: 0 for v in vertices}

print(parent)

# Union-Find
def find(v):
    print(parent)
    if parent[v] != v:
        parent[v] = find(parent[v])
    return parent[v]

def union(u, v):
    ru, rv = find(u), find(v)
    
    if ru == rv:
        return False
    
    if rank[ru] < rank[rv]:
        parent[ru] = rv
    elif rank[ru] > rank[rv]:
        parent[rv] = ru
    else:
        parent[ru] = rv
        rank[rv] += 1
        
    return True
                
                
mst = []
total_cost = 0
for w, u, v in edges:
    if union(u, v):
        mst.append((w, u, v))
        total_cost += w
        
print("Arestas da MST:", mst)
print("Custo total da MST:", total_cost)
