import sys


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
tree = [0] * (4 * n)
flipped = bytearray(4 * n)


def apply(node, length):
    tree[node] = length - tree[node]
    flipped[node] ^= 1


def push(node, left, right):
    if flipped[node] and left != right:
        middle = (left + right) // 2
        apply(node * 2, middle - left + 1)
        apply(node * 2 + 1, right - middle)
        flipped[node] = 0


def update(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        apply(node, right - left + 1)
        return
    push(node, left, right)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right)
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


answers = []
for _ in range(operations):
    operation, left, right = map(int, input().split())
    if operation == 0:
        update(1, 1, n, left, right)
    else:
        answers.append(str(query(1, 1, n, left, right)))
print("\n".join(answers))
