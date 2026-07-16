import sys
from array import array


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
values = array("q", map(int, input().split()))
maximum = array("q", [0]) * (4 * n)
addition = array("q", [0]) * (4 * n)
assigned = array("q", [0]) * (4 * n)
has_assignment = bytearray(4 * n)


def build(node, left, right):
    if left == right:
        maximum[node] = values[left - 1]
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    maximum[node] = max(maximum[node * 2], maximum[node * 2 + 1])


def set_value(node, value):
    maximum[node] = assigned[node] = value
    addition[node] = 0
    has_assignment[node] = 1


def add_value(node, value):
    maximum[node] += value
    if has_assignment[node]:
        assigned[node] += value
    else:
        addition[node] += value


def push(node, left, right):
    if left == right:
        return
    child_left, child_right = node * 2, node * 2 + 1
    middle = (left + right) // 2
    if has_assignment[node]:
        set_value(child_left, assigned[node])
        set_value(child_right, assigned[node])
        has_assignment[node] = 0
    if addition[node]:
        add_value(child_left, addition[node])
        add_value(child_right, addition[node])
        addition[node] = 0


def update(node, left, right, query_left, query_right, operation, value):
    if query_left <= left and right <= query_right:
        (set_value if operation == 1 else add_value)(node, value)
        return
    push(node, left, right)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right, operation, value)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right, operation, value)
    maximum[node] = max(maximum[node * 2], maximum[node * 2 + 1])


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return maximum[node]
    push(node, left, right)
    middle = (left + right) // 2
    answer = -10**30
    if query_left <= middle:
        answer = max(answer, query(node * 2, left, middle, query_left, query_right))
    if middle < query_right:
        answer = max(answer, query(node * 2 + 1, middle + 1, right, query_left, query_right))
    return answer


build(1, 1, n)
answers = []
for _ in range(operations):
    operation = list(map(int, input().split()))
    if operation[0] == 3:
        answers.append(str(query(1, 1, n, operation[1], operation[2])))
    else:
        update(1, 1, n, operation[1], operation[2], operation[0], operation[3])
print("\n".join(answers))
