import sys


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
length, colors, operations = map(int, input().split())
tree = [1] * (4 * length)
lazy = [1] * (4 * length)


def apply(node, color_mask):
    tree[node] = lazy[node] = color_mask


def push(node):
    if lazy[node]:
        apply(node * 2, lazy[node])
        apply(node * 2 + 1, lazy[node])
        lazy[node] = 0


def update(node, left, right, query_left, query_right, color_mask):
    if query_left <= left and right <= query_right:
        apply(node, color_mask)
        return
    push(node)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right, color_mask)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right, color_mask)
    tree[node] = tree[node * 2] | tree[node * 2 + 1]


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return tree[node]
    push(node)
    middle = (left + right) // 2
    answer = 0
    if query_left <= middle:
        answer |= query(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        answer |= query(node * 2 + 1, middle + 1, right, query_left, query_right)
    return answer


answers = []
for _ in range(operations):
    operation = input().split()
    if operation[0] == b'C':
        left, right, color = map(int, operation[1:])
        if left > right:
            left, right = right, left
        update(1, 1, length, left, right, 1 << (color - 1))
    else:
        left, right = map(int, operation[1:])
        if left > right:
            left, right = right, left
        answers.append(str(query(1, 1, length, left, right).bit_count()))
print("\n".join(answers))
