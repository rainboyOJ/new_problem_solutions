import sys
from array import array
from math import isqrt


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n = int(input())
values = array("q", map(int, input().split()))
operations = int(input())
total = array("q", [0]) * (4 * n)
minimum = array("q", [0]) * (4 * n)
maximum = array("q", [0]) * (4 * n)
assigned = array("q", [0]) * (4 * n)


def apply(node, value, length):
    total[node] = value * length
    minimum[node] = maximum[node] = value
    assigned[node] = value


def build(node, left, right):
    if left == right:
        total[node] = minimum[node] = maximum[node] = values[left - 1]
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    pull(node)


def pull(node):
    left, right = node * 2, node * 2 + 1
    total[node] = total[left] + total[right]
    minimum[node] = min(minimum[left], minimum[right])
    maximum[node] = max(maximum[left], maximum[right])


def push(node, left, right):
    if assigned[node] and left != right:
        middle = (left + right) // 2
        apply(node * 2, assigned[node], middle - left + 1)
        apply(node * 2 + 1, assigned[node], right - middle)
        assigned[node] = 0


def update(node, left, right, query_left, query_right):
    if query_right < left or right < query_left or maximum[node] <= 1:
        return
    if query_left <= left and right <= query_right and minimum[node] == maximum[node]:
        apply(node, isqrt(maximum[node]), right - left + 1)
        return
    push(node, left, right)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right)
    pull(node)


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return total[node]
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
    kind, left, right = map(int, input().split())
    if left > right:
        left, right = right, left
    if kind:
        answers.append(str(query(1, 1, n, left, right)))
    else:
        update(1, 1, n, left, right)
print("\n".join(answers))
