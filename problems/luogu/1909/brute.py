import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


data = read_all_ints()
n = data[0]
answer = 10**18
for i in range(1, 7, 2):
    count, price = data[i], data[i + 1]
    packs = 0
    while packs * count < n:
        packs += 1
    answer = min(answer, packs * price)
print(answer, end="")
