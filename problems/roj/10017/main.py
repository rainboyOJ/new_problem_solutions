import sys

# 增加递归深度，虽然本题非递归也为了防止意外
sys.setrecursionlimit(2000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    A = [int(x) for x in input_data[1:]]
    
    MOD = 10**9 + 7
    
    fact = [1] * (n + 1)
    inv = [1] * (n + 1)
    
    for i in range(1, n + 1):
        fact[i] = (fact[i-1] * i) % MOD
        
    inv[n] = pow(fact[n], MOD - 2, MOD)
    for i in range(n - 1, -1, -1):
        inv[i] = (inv[i+1] * (i + 1)) % MOD
        
    def comb(n, k):
        if k < 0 or k > n:
            return 0
        return fact[n] * inv[k] % MOD * inv[n-k] % MOD

    ans = 0
    if n % 2 == 1:
        k = n // 2
        for j in range(n):
            if j % 2 != 0:
                continue
            p = j // 2
            c = comb(k, p)
            if p % 2 == 1:
                c = -c
            ans = (ans + A[j] * c) % MOD
    else:
        k = n // 2
        for j in range(n):
            p = j // 2
            c = comb(k - 1, p)
            if p % 2 == 1:
                c = -c
            ans = (ans + A[j] * c) % MOD
            
    print((ans % MOD + MOD) % MOD)

if __name__ == '__main__':
    solve()
