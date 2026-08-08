import sys


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
values = list(map(int, input().split()))
tree = [0] * (4 * n)
lazy = [0] * (4 * n)


def build(node, left, right):
    if left == right:
        tree[node] = values[left - 1]
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


def apply(node, length, value):
    tree[node] += length * value
    lazy[node] += value


def push(node, left, right):
    if lazy[node] and left != right:
        middle = (left + right) // 2
        apply(node * 2, middle - left + 1, lazy[node])
        apply(node * 2 + 1, right - middle, lazy[node])
        lazy[node] = 0


def update(node, left, right, query_left, query_right, value):
    if query_left <= left and right <= query_right:
        apply(node, right - left + 1, value)
        return
    push(node, left, right)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right, value)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right, value)
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return tree[node]
    push(node, left, right)
    middle = (left + right) // 2
    answer = 0
    if query_left <= middle:
        answer += query(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        answer += query(node * 2 + 1, middle + 1, right, query_left, query_right)
    return answer


build(1, 1, n)
answers = []
for _ in range(operations):
    operation = list(map(int, input().split()))
    if operation[0] == 1:
        update(1, 1, n, operation[1], operation[2], operation[3])
    else:
        answers.append(str(query(1, 1, n, operation[1], operation[2])))
print("\n".join(answers))
