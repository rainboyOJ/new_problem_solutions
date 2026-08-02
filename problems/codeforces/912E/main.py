import sys


LIMIT = 10**18
input = sys.stdin.buffer.readline
n = int(input())
primes = list(map(int, input().split()))
rank = int(input())


def products(selected):
    result = []

    def dfs(index, value):
        if index == len(selected):
            result.append(value)
            return
        prime = selected[index]
        while value <= LIMIT:
            dfs(index + 1, value)
            if value > LIMIT // prime:
                break
            value *= prime

    dfs(0, 1)
    return sorted(result)


left = products(primes[::2])
right = products(primes[1::2])


def count_not_greater(limit):
    count = 0
    j = len(right) - 1
    for value in left:
        while j >= 0 and value > limit // right[j]:
            j -= 1
        if j < 0:
            break
        count += j + 1
    return count


low, high = 1, LIMIT
while low < high:
    middle = (low + high) // 2
    if count_not_greater(middle) >= rank:
        high = middle
    else:
        low = middle + 1
print(low)
