import random
import sys
from array import array
from bisect import bisect_left


data = iter(map(int, sys.stdin.buffer.read().split()))
n, required = next(data), next(data)
events = [(next(data), next(data)) for _ in range(n)]
coordinates = sorted({value for event in events for value in event})
compressed = [(bisect_left(coordinates, left), bisect_left(coordinates, right))
              for left, right in events]
coordinate_count = len(coordinates)

next_end = array("i", [coordinate_count]) * (coordinate_count + 1)
for left, right in compressed:
    if right < next_end[left]:
        next_end[left] = right
for i in range(coordinate_count - 1, -1, -1):
    if next_end[i + 1] < next_end[i]:
        next_end[i] = next_end[i + 1]

jump = [next_end]
for _ in range(1, n.bit_length() + 1):
    previous = jump[-1]
    jump.append(array("i", map(previous.__getitem__, previous)))


def query(left, right):
    count = 0
    current = left
    for level in range(len(jump) - 1, -1, -1):
        destination = jump[level][current]
        if destination <= right:
            current = destination
            count += 1 << level
    return count


# Randomized treap of disjoint free intervals, keyed by left endpoint.
random.seed(20260716)
left_child = [0]
right_child = [0]
priority = [0]
key = [0]
value = [0]


def new_node(left, right):
    left_child.append(0)
    right_child.append(0)
    priority.append(random.randrange(1 << 30))
    key.append(left)
    value.append(right)
    return len(key) - 1


def split(root, split_key):
    if not root:
        return 0, 0
    if key[root] < split_key:
        left_tree, right_tree = split(right_child[root], split_key)
        right_child[root] = left_tree
        return root, right_tree
    left_tree, right_tree = split(left_child[root], split_key)
    left_child[root] = right_tree
    return left_tree, root


def merge(left_root, right_root):
    if not left_root or not right_root:
        return left_root or right_root
    if priority[left_root] < priority[right_root]:
        right_child[left_root] = merge(right_child[left_root], right_root)
        return left_root
    left_child[right_root] = merge(left_root, left_child[right_root])
    return right_root


def insert(root, node):
    if not root or priority[node] < priority[root]:
        left_child[node], right_child[node] = split(root, key[node])
        return node
    if key[node] < key[root]:
        left_child[root] = insert(left_child[root], node)
    else:
        right_child[root] = insert(right_child[root], node)
    return root


def erase(root, target_key):
    if key[root] == target_key:
        return merge(left_child[root], right_child[root])
    if target_key < key[root]:
        left_child[root] = erase(left_child[root], target_key)
    else:
        right_child[root] = erase(right_child[root], target_key)
    return root


def predecessor(root, target_key):
    result = 0
    while root:
        if key[root] <= target_key:
            result = root
            root = right_child[root]
        else:
            root = left_child[root]
    return result


root = new_node(0, coordinate_count - 1)
available = query(0, coordinate_count - 1)
chosen = []

for identity, (event_left, event_right) in enumerate(compressed, 1):
    node = predecessor(root, event_left)
    if not node or value[node] < event_right:
        continue
    free_left, free_right = key[node], value[node]
    remaining = (available - query(free_left, free_right)
                 + query(free_left, event_left) + query(event_right, free_right))
    if remaining >= required - len(chosen) - 1:
        chosen.append(identity)
        available = remaining
        root = erase(root, free_left)
        root = insert(root, new_node(free_left, event_left))
        root = insert(root, new_node(event_right, free_right))
        if len(chosen) == required:
            break

print("\n".join(map(str, chosen)) if len(chosen) == required else -1)
