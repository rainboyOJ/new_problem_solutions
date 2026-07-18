import sys
from collections import deque

def topological_status(graph, indegree, n):
    degree = indegree.copy()
    queue = deque(node for node in range(n) if degree[node] == 0)
    order = []
    unique = True

    while queue:
        if len(queue) > 1:
            unique = False
        node = queue.popleft()
        order.append(node)
        for neighbor in range(n):
            if graph[node][neighbor]:
                degree[neighbor] -= 1
                if degree[neighbor] == 0:
                    queue.append(neighbor)

    if len(order) < n:
        return "inconsistent", order
    return ("determined" if unique else "unknown"), order

def main():
    read = sys.stdin.buffer.readline
    n, m = map(int, read().split())
    relations = [read().strip() for _ in range(m)]
    graph = [bytearray(n) for _ in range(n)]
    indegree = [0] * n

    for index, relation in enumerate(relations, 1):
        smaller, larger = relation[0] - 65, relation[2] - 65
        if not graph[smaller][larger]:
            graph[smaller][larger] = 1
            indegree[larger] += 1

        status, order = topological_status(graph, indegree, n)
        if status == "inconsistent":
            print(f"Inconsistency found after {index} relations.")
            return
        if status == "determined":
            sequence = "".join(chr(node + 65) for node in order)
            print(f"Sorted sequence determined after {index} relations: {sequence}.")
            return

    print("Sorted sequence cannot be determined.")

if __name__ == "__main__":
    main()
