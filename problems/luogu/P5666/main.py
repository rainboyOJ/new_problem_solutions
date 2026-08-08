import sys
from array import array


input = sys.stdin.buffer.readline
test_cases = int(input())
answers = []
for _ in range(test_cases):
    n = int(input())
    graph = [[] for _ in range(n + 1)]
    for __ in range(n - 1):
        u, v = map(int, input().split())
        graph[u].append(v)
        graph[v].append(u)

    parent = array("i", [0]) * (n + 1)
    order = array("i", [1])
    for node in order:
        for neighbor in graph[node]:
            if neighbor != parent[node]:
                parent[neighbor] = node
                order.append(neighbor)
    subtree = array("i", [1]) * (n + 1)
    subtree[0] = 0
    heavy = array("i", [0]) * (n + 1)
    for node in reversed(order[1:]):
        subtree[parent[node]] += subtree[node]
        if subtree[node] > subtree[heavy[parent[node]]]:
            heavy[parent[node]] = node

    log = n.bit_length()
    jump = [array("i", [0]) * (n + 1) for _ in range(log)]
    for node in range(1, n + 1):
        jump[0][node] = heavy[node]
    for level in range(1, log):
        previous, current = jump[level - 1], jump[level]
        for node in range(1, n + 1):
            current[node] = previous[previous[node]]

    def rebuild(node):
        for level in range(1, log):
            jump[level][node] = jump[level - 1][jump[level - 1][node]]

    def centroid_sum(root):
        total = subtree[root]
        node = root
        for level in range(log - 1, -1, -1):
            candidate = jump[level][node]
            if candidate and subtree[candidate] * 2 >= total:
                node = candidate
        value = node
        if subtree[node] * 2 == total:
            value += parent[node]
        return value

    answer = 0
    # A frame stores the next adjacency position and the two largest current
    # neighbour components. Mutations are rolled back after returning.
    def largest_two(node):
        first = second = 0
        for neighbor in graph[node]:
            if subtree[neighbor] >= subtree[first]:
                second, first = first, neighbor
            elif subtree[neighbor] > subtree[second]:
                second = neighbor
        return first, second

    first, second = largest_two(1)
    stack = [[1, 0, 0, first, second, None]]
    while stack:
        frame = stack[-1]
        node, father, index, first, second, restore = frame
        if index == len(graph[node]):
            stack.pop()
            if restore is not None:
                (old_parent_node, old_parent_child, old_node_size,
                 old_child_size, old_jump, changed_node, changed_child) = restore
                parent[changed_node] = old_parent_node
                parent[changed_child] = old_parent_child
                subtree[changed_node] = old_node_size
                subtree[changed_child] = old_child_size
                jump[0][changed_node] = old_jump
                rebuild(changed_node)
            continue
        neighbor = graph[node][index]
        frame[2] += 1
        if neighbor == father:
            continue
        answer += centroid_sum(neighbor)
        old_state = (parent[node], parent[neighbor], subtree[node],
                     subtree[neighbor], jump[0][node], node, neighbor)
        alternate = second if neighbor == first else first
        jump[0][node] = alternate
        rebuild(node)
        subtree[node] -= subtree[neighbor]
        subtree[neighbor] += subtree[node]
        parent[node] = neighbor
        parent[neighbor] = father
        answer += centroid_sum(node)
        child_first, child_second = largest_two(neighbor)
        stack.append([neighbor, node, 0, child_first, child_second, old_state])

    answers.append(str(answer))
print("\n".join(answers))
