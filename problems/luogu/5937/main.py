import sys


input = sys.stdin.buffer.readline
_ = int(input())
m = int(input())
parent = {}
size = {}
parity = {}


def add(x):
    if x not in parent:
        parent[x] = x
        size[x] = 1
        parity[x] = 0


def find(x):
    if parent[x] != x:
        old_parent = parent[x]
        parent[x] = find(old_parent)
        parity[x] ^= parity[old_parent]
    return parent[x]


def unite(x, y, expected):
    root_x, root_y = find(x), find(y)
    relation = parity[x] ^ parity[y] ^ expected
    if root_x == root_y:
        return relation == 0
    if size[root_x] < size[root_y]:
        root_x, root_y = root_y, root_x
    parent[root_y] = root_x
    parity[root_y] = relation
    size[root_x] += size[root_y]
    return True


answer = m
for i in range(m):
    left, right, word = input().split()
    left, right = int(left) - 1, int(right)
    add(left)
    add(right)
    if answer == m and not unite(left, right, word == b"odd"):
        answer = i

print(answer)
