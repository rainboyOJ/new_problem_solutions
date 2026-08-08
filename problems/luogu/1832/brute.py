import sys

data = sys.stdin.buffer.read().split()
n = int(data[0])

limit = n
is_prime = [True] * (limit + 1)
is_prime[0] = is_prime[1] = False
for i in range(2, limit + 1):
    if is_prime[i]:
        for j in range(i * i, limit + 1, i):
            is_prime[j] = False

primes = [i for i, p in enumerate(is_prime) if p]

ans = 0

def dfs(idx, cur):
    global ans
    if cur > n:
        return
    if idx == len(primes):
        if cur == n:
            ans += 1
        return
    p = primes[idx]
    k = 0
    while cur + k * p <= n:
        dfs(idx + 1, cur + k * p)
        k += 1

dfs(0, 0)
print(ans)
