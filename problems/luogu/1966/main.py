import sys


MOD = 10**8 - 3
data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
first = [next(data) for _ in range(n)]
second = [next(data) for _ in range(n)]
target = [0] * n

for first_index, second_index in zip(
    sorted(range(n), key=first.__getitem__),
    sorted(range(n), key=second.__getitem__),
):
    target[first_index] = second_index

tree = [0] * (n + 1)
answer = 0
for seen, position in enumerate(target):
    index = position + 1
    prefix = 0
    i = index
    while i:
        prefix += tree[i]
        i -= i & -i
    answer += seen - prefix
    while index <= n:
        tree[index] += 1
        index += index & -index

print(answer % MOD)
