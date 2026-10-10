def power(base, exp, mod):
    res = 1
    base %= mod
    while exp > 0:
        if exp % 2 == 1:
            res = (res * base) % mod
        base = (base * base) % mod
        exp //= 2
    return res

def solve():
    import sys
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n, m = map(int, input_data[:2])
    
    if n > m:
        n, m = m, n
        
    MOD = 1000000007
    
    if n == 1:
        print(power(2, m, MOD))
        return
        
    A = [0, 0, 12, 112, 912, 7136, 56768, 453504, 3626752]
    B = [0, 0, 36, 336, 2688, 21312, 170112, 1360128, 10879488]
    
    if n <= 8:
        if n == m:
            print(A[n])
        else:
            print((B[n] * power(3, m - n - 1, MOD)) % MOD)
    else:
        print(0)

if __name__ == '__main__':
    solve()
