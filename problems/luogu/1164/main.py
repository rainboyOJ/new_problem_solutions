n, target = map(int, input().split())
prices = list(map(int, input().split()))

dp = [0] * (target + 1)
dp[0] = 1

for price in prices:
    for money in range(target, price - 1, -1):
        dp[money] += dp[money - price]

print(dp[target])
