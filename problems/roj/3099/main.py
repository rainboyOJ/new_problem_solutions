import sys
from math import gcd

def solve() -> None:
    """解 (m-n)*t ≡ (y-x) (mod L)：扩展欧几里得 + 最小非负解。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    x, y, m, n, L = next(data), next(data), next(data), next(data), next(data)
    a, b, mod = m - n, y - x, L           # a*t ≡ b (mod L)
    g = gcd(a, mod)                       # gcd 可能取到 0 当且仅当 a=0
    if b % g:                             # b 不是 g 的倍数 => 无解
        print("Impossible")
        return
    a, b, mod = a // g, b // g, mod // g  # 归一化：a*t ≡ b (mod mod)，gcd(a,mod)=1
    # a 的逆元 mod 意义下：pow(a, -1, mod)（Python 3.8+，内部扩展欧几里得）
    print(b * pow(a, -1, mod) % mod)

solve()
