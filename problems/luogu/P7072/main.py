import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, percentage = next(data), next(data)
tree = [0] * 602


def add(index):
    index += 1
    while index < len(tree):
        tree[index] += 1
        index += index & -index


def kth(k):
    index = 0
    step = 1 << (len(tree).bit_length() - 1)
    while step:
        next_index = index + step
        if next_index < len(tree) and tree[next_index] < k:
            index = next_index
            k -= tree[next_index]
        step >>= 1
    return index


answer = []
for seen, score in enumerate(data, 1):
    add(score)
    winners = max(1, seen * percentage // 100)
    answer.append(kth(seen - winners + 1))
print(*answer)
