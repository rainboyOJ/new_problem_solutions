MOD = 10000

n = int(input())

if n == 1:
    print(1)
elif n == 2:
    print(2)
else:
    dp = [0] * (n + 1)
    dp[0] = 1
    dp[1] = 1
    dp[2] = 2

    for length in range(3, n + 1):
        dp[length] = (2 * dp[length - 1] + dp[length - 3]) % MOD

    print(dp[n])
