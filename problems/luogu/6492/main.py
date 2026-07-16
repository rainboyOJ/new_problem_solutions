import sys
from array import array


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
first = bytearray(4 * n)
last = bytearray(4 * n)
prefix = array("i", [0]) * (4 * n)
suffix = array("i", [0]) * (4 * n)
best = array("i", [0]) * (4 * n)


def pull(node, left_length, right_length):
    left, right = node * 2, node * 2 + 1
    different = last[left] != first[right]
    first[node] = first[left]
    last[node] = last[right]
    prefix[node] = prefix[left] + prefix[right] if different and prefix[left] == left_length else prefix[left]
    suffix[node] = suffix[right] + suffix[left] if different and suffix[right] == right_length else suffix[right]
    best[node] = max(best[left], best[right], suffix[left] + prefix[right] if different else 0)


def build(node, left, right):
    prefix[node] = suffix[node] = best[node] = right - left + 1
    if left == right:
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    pull(node, middle - left + 1, right - middle)


def update(node, left, right, position):
    if left == right:
        first[node] ^= 1
        last[node] = first[node]
        return
    middle = (left + right) // 2
    if position <= middle:
        update(node * 2, left, middle, position)
    else:
        update(node * 2 + 1, middle + 1, right, position)
    pull(node, middle - left + 1, right - middle)


build(1, 1, n)
answers = []
for _ in range(operations):
    position = int(input())
    update(1, 1, n, position)
    answers.append(str(best[1]))
print("\n".join(answers))
