import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    k = int(input_data[1])
    
    a = [0] * (n + 2)
    for i in range(1, n + 1):
        a[i] = int(input_data[1 + i])
        
    dp = [[[0, 0] for _ in range(k + 1)] for _ in range(n + 1)]
    ans = 0
    
    for i in range(2, n):
        for j in range(k + 1):
            if a[i] < a[i-1] and a[i] < a[i+1]:
                dp[i][j][1] = dp[i-1][j][0] + a[i]
                dp[i][j][0] = dp[i-1][j][1]
            else:
                if j > 0:
                    dp[i][j][1] = dp[i-1][j-1][0] + min(a[i-1] - 1, a[i+1] - 1)
                dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1])
                
            ans = max(ans, dp[i][j][0], dp[i][j][1])
            
    print(ans)

if __name__ == '__main__':
    solve()
