#!/usr/bin/env python3
import random


def feasible(start, finish, graph, station, repaired):
    parent = [0] * len(graph)
    parent_edge = [0] * len(graph)
    queue = [start]
    parent[start] = -1
    for u in queue:
        for v, edge_id in graph[u]:
            if parent[v] != 0:
                continue
            parent[v] = u
            parent_edge[v] = edge_id
            queue.append(v)
    path = []
    current = finish
    while current != start:
        path.append((current, parent_edge[current]))
        current = parent[current]
    path.append((start, 0))
    path.reverse()

    broken = 0
    for i in range(1, len(path)):
        if not repaired[path[i][1]]:
            broken += 1
        if station[path[i][0]]:
            broken = 0
        if broken > 1:
            return False
    return True


def main():
    random.seed()
    n = random.randint(2, 10)
    x_code = random.randint(0, 1)
    edges = []
    graph = [[] for _ in range(n + 1)]
    parent = [0] * (n + 1)
    parent_edge = [0] * (n + 1)
    for vertex in range(2, n + 1):
        father = random.randint(1, vertex - 1)
        edge_id = len(edges) + 1
        edges.append((father, vertex))
        graph[father].append((vertex, edge_id))
        graph[vertex].append((father, edge_id))
        parent[vertex] = father
        parent_edge[vertex] = edge_id

    order = [1]
    for u in order:
        for v, _ in graph[u]:
            if v == parent[u]:
                continue
            parent[v] = u
            parent_edge[v] = next(
                i + 1 for i, edge in enumerate(edges)
                if set(edge) == set((u, v))
            )
            order.append(v)

    station_vertices = random.sample(range(1, n + 1), random.randint(1, n))
    station = [False] * (n + 1)
    for u in station_vertices:
        station[u] = True

    plan_count = random.randint(1, 15)
    plans = []
    for _ in range(plan_count):
        start = random.randint(1, n)
        finish = random.randint(1, n)
        while finish == start:
            finish = random.randint(1, n)
        plans.append((start, finish))

    operation_count = random.randint(1, 30)
    edge_order = list(range(1, n))
    random.shuffle(edge_order)
    operation_count = min(operation_count, n - 1 + 15)
    actual_operations = []
    repaired = [False] * n
    last_answer = 0
    for _ in range(operation_count):
        can_repair = any(not repaired[i] for i in range(1, n))
        if can_repair and random.random() < 0.55:
            choices = [i for i in range(1, n) if not repaired[i]]
            edge_id = random.choice(choices)
            repaired[edge_id] = True
            u, v = edges[edge_id - 1]
            actual_operations.append((1, u ^ (x_code * last_answer),
                                      v ^ (x_code * last_answer)))
        else:
            actual_operations.append((2,))
            answer = sum(
                feasible(start, finish, graph, station, repaired)
                for start, finish in plans
            )
            last_answer = answer

    print(n, x_code)
    for u, v in edges:
        print(u, v)
    print(len(station_vertices))
    print(*station_vertices)
    print(plan_count)
    for start, finish in plans:
        print(start, finish)
    print(len(actual_operations))
    for operation in actual_operations:
        print(*operation)


if __name__ == "__main__":
    main()
