import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, w = data[0], data[1]
coins = data[2:2 + n]

MOD = 10 ** 9 + 7
dp = [0] * (w + 1)
dp[0] = 1
for c in coins:
    for j in range(c, w + 1):
        dp[j] = (dp[j] + dp[j - c]) % MOD
print(dp[w])
