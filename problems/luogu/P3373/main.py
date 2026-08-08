import sys


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations, modulus = map(int, input().split())
values = list(map(int, input().split()))
tree = [0] * (4 * n)
multiply = [1] * (4 * n)
addition = [0] * (4 * n)


def build(node, left, right):
    if left == right:
        tree[node] = values[left - 1] % modulus
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % modulus


def apply(node, length, mul, add):
    tree[node] = (tree[node] * mul + length * add) % modulus
    multiply[node] = multiply[node] * mul % modulus
    addition[node] = (addition[node] * mul + add) % modulus


def push(node, left, right):
    if left == right or (multiply[node] == 1 and addition[node] == 0):
        return
    middle = (left + right) // 2
    apply(node * 2, middle - left + 1, multiply[node], addition[node])
    apply(node * 2 + 1, right - middle, multiply[node], addition[node])
    multiply[node], addition[node] = 1, 0


def update(node, left, right, query_left, query_right, mul, add):
    if query_left <= left and right <= query_right:
        apply(node, right - left + 1, mul, add)
        return
    push(node, left, right)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right, mul, add)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right, mul, add)
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % modulus


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
    return answer % modulus


build(1, 1, n)
answers = []
for _ in range(operations):
    operation = list(map(int, input().split()))
    if operation[0] == 1:
        update(1, 1, n, operation[1], operation[2], operation[3] % modulus, 0)
    elif operation[0] == 2:
        update(1, 1, n, operation[1], operation[2], 1, operation[3] % modulus)
    else:
        answers.append(str(query(1, 1, n, operation[1], operation[2])))
print("\n".join(answers))
