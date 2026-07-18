n = int(input())

dp = [0] * (n + 1)
for value in range(1, n + 1):
    dp[value] = 1
    for next_value in range(1, value // 2 + 1):
        dp[value] += dp[next_value]

print(dp[n])
