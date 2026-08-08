import sys
from array import array


MAX_BIT = 29
input = sys.stdin.buffer.readline
n, query_count = map(int, input().split())
values = array("I", map(int, input().split()))
graph = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    graph[u].append(v)
    graph[v].append(u)

parent = array("i", [-1]) * n
depth = array("i", [0]) * n
entry = array("i", [0]) * n
exit = array("i", [0]) * n
order = array("i")
stack = [(0, -1, False)]

while stack:
    node, previous, leaving = stack.pop()
    if leaving:
        exit[node] = len(order) - 1
        continue
    parent[node] = previous
    depth[node] = depth[previous] + 1 if previous >= 0 else 0
    entry[node] = len(order)
    order.append(node)
    stack.append((node, previous, True))
    stack.extend((neighbor, node, False)
                 for neighbor in reversed(graph[node]) if neighbor != previous)
del graph, stack

jump = [array("i", (previous if previous >= 0 else 0 for previous in parent))]
for _ in range(1, n.bit_length()):
    previous = jump[-1]
    jump.append(array("i", map(previous.__getitem__, previous)))


def lca(first, second):
    if depth[first] < depth[second]:
        first, second = second, first
    difference = depth[first] - depth[second]
    level = 0
    while difference:
        if difference & 1:
            first = jump[level][first]
        difference >>= 1
        level += 1
    if first == second:
        return first
    for level in range(len(jump) - 1, -1, -1):
        if jump[level][first] != jump[level][second]:
            first, second = jump[level][first], jump[level][second]
    return jump[0][first]


child_zero = array("i", [0])
child_one = array("i", [0])
count = array("i", [0])


def clone(node):
    child_zero.append(child_zero[node])
    child_one.append(child_one[node])
    count.append(count[node])
    return len(count) - 1


def insert(previous_root, value):
    root = clone(previous_root)
    count[root] += 1
    previous, current = previous_root, root
    for bit in range(MAX_BIT, -1, -1):
        if value >> bit & 1:
            child = clone(child_one[previous])
            child_one[current] = child
            previous = child_one[previous]
        else:
            child = clone(child_zero[previous])
            child_zero[current] = child
            previous = child_zero[previous]
        current = child
        count[current] += 1
    return root


path_root = array("i", [0]) * n
for node in order:
    previous_root = path_root[parent[node]] if parent[node] >= 0 else 0
    path_root[node] = insert(previous_root, values[node])

euler_root = array("i", [0])
for node in order:
    euler_root.append(insert(euler_root[-1], values[node]))


def range_maximum(older_root, newer_root, value):
    answer = 0
    for bit in range(MAX_BIT, -1, -1):
        if value >> bit & 1:
            wanted_old, wanted_new = child_zero[older_root], child_zero[newer_root]
            other_old, other_new = child_one[older_root], child_one[newer_root]
        else:
            wanted_old, wanted_new = child_one[older_root], child_one[newer_root]
            other_old, other_new = child_zero[older_root], child_zero[newer_root]
        if count[wanted_new] > count[wanted_old]:
            answer |= 1 << bit
            older_root, newer_root = wanted_old, wanted_new
        else:
            older_root, newer_root = other_old, other_new
    return answer


def path_maximum(first_root, second_root, lca_root, parent_root, value):
    answer = 0
    for bit in range(MAX_BIT, -1, -1):
        children = child_zero if value >> bit & 1 else child_one
        other = child_one if value >> bit & 1 else child_zero
        first_child, second_child = children[first_root], children[second_root]
        lca_child, parent_child = children[lca_root], children[parent_root]
        if count[first_child] + count[second_child] > count[lca_child] + count[parent_child]:
            answer |= 1 << bit
            first_root, second_root = first_child, second_child
            lca_root, parent_root = lca_child, parent_child
        else:
            first_root, second_root = other[first_root], other[second_root]
            lca_root, parent_root = other[lca_root], other[parent_root]
    return answer


answers = []
for _ in range(query_count):
    query = list(map(int, input().split()))
    if query[0] == 1:
        node, value = query[1] - 1, query[2]
        answers.append(str(range_maximum(euler_root[entry[node]],
                                         euler_root[exit[node] + 1], value)))
    else:
        first, second, value = query[1] - 1, query[2] - 1, query[3]
        ancestor = lca(first, second)
        ancestor_parent = parent[ancestor]
        answers.append(str(path_maximum(path_root[first], path_root[second],
                                        path_root[ancestor],
                                        path_root[ancestor_parent] if ancestor_parent >= 0 else 0,
                                        value)))

print("\n".join(answers))
