import sys
from array import array


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
values = array("q", (int(input()) for _ in range(n)))
total = array("q", [0]) * (4 * n)
prefix = array("q", [0]) * (4 * n)
suffix = array("q", [0]) * (4 * n)
best = array("q", [0]) * (4 * n)


def pull(node):
    left, right = node * 2, node * 2 + 1
    total[node] = total[left] + total[right]
    prefix[node] = max(prefix[left], total[left] + prefix[right])
    suffix[node] = max(suffix[right], total[right] + suffix[left])
    best[node] = max(best[left], best[right], suffix[left] + prefix[right])


def build(node, left, right):
    if left == right:
        total[node] = prefix[node] = suffix[node] = best[node] = values[left - 1]
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    pull(node)


def update(node, left, right, position, value):
    if left == right:
        total[node] = prefix[node] = suffix[node] = best[node] = value
        return
    middle = (left + right) // 2
    if position <= middle:
        update(node * 2, left, middle, position, value)
    else:
        update(node * 2 + 1, middle + 1, right, position, value)
    pull(node)


def merge(a, b):
    at, ap, ass, ab, al = a
    bt, bp, bs, bb, bl = b
    return (at + bt, max(ap, at + bp), max(bs, bt + ass),
            max(ab, bb, ass + bp), al + bl)


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return total[node], prefix[node], suffix[node], best[node], right - left + 1
    middle = (left + right) // 2
    result = None
    if query_left <= middle:
        result = query(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        right_result = query(node * 2 + 1, middle + 1, right, query_left, query_right)
        result = right_result if result is None else merge(result, right_result)
    return result


build(1, 1, n)
answers = []
for _ in range(operations):
    operation, x, y = map(int, input().split())
    if operation == 1:
        if x > y:
            x, y = y, x
        answers.append(str(query(1, 1, n, x, y)[3]))
    else:
        update(1, 1, n, x, y)
print("\n".join(answers))
