import sys
from array import array


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
values = array("d", map(float, input().split()))
summation = array("d", [0.0]) * (4 * n)
squared = array("d", [0.0]) * (4 * n)
lazy = array("d", [0.0]) * (4 * n)


def apply(node, length, value):
    summation[node] += length * value
    squared[node] += 2 * value * summation[node] - length * value * value
    lazy[node] += value


def build(node, left, right):
    if left == right:
        summation[node] = values[left - 1]
        squared[node] = values[left - 1] ** 2
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    summation[node] = summation[node * 2] + summation[node * 2 + 1]
    squared[node] = squared[node * 2] + squared[node * 2 + 1]


def push(node, left, right):
    if lazy[node] == 0 or left == right:
        return
    middle = (left + right) // 2
    apply(node * 2, middle - left + 1, lazy[node])
    apply(node * 2 + 1, right - middle, lazy[node])
    lazy[node] = 0.0


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
    summation[node] = summation[node * 2] + summation[node * 2 + 1]
    squared[node] = squared[node * 2] + squared[node * 2 + 1]


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return summation[node], squared[node]
    push(node, left, right)
    middle = (left + right) // 2
    result_sum = result_square = 0.0
    if query_left <= middle:
        result_sum, result_square = query(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        right_sum, right_square = query(node * 2 + 1, middle + 1, right, query_left, query_right)
        result_sum += right_sum
        result_square += right_square
    return result_sum, result_square


build(1, 1, n)
answers = []
for _ in range(operations):
    operation = input().split()
    kind, left, right = int(operation[0]), int(operation[1]), int(operation[2])
    if kind == 1:
        update(1, 1, n, left, right, float(operation[3]))
    else:
        count = right - left + 1
        total_value, total_square = query(1, 1, n, left, right)
        if kind == 2:
            answers.append(f"{total_value / count:.4f}")
        else:
            answers.append(f"{total_square / count - (total_value / count) ** 2:.4f}")
print("\n".join(answers))
