n = int(input())
dp = [0] * (n + 1)
for value in range(1, n + 1):
    dp[value] = 1 + sum(dp[1:value // 2 + 1])
print(dp[n])
