# brute.py：小数据暴力解，模拟 Bessie 舍入和 Elsie 链式舍入，逐个数检查。
import sys

def round_to(a, b):
    """Bessie 舍入：将 a 四舍五入到最接近的 10^b。"""
    digit = (a // (10 ** (b - 1))) % 10
    if digit >= 5:
        a += 10 ** b
    a = (a // (10 ** b)) * (10 ** b)
    return a

def chain_round(a, b):
    """Elsie 链式舍入：先舍入到 10^1，再 10^2，...，直到 10^b。"""
    for i in range(1, b + 1):
        a = round_to(a, i)
    return a

def get_P(x):
    """P = 满足 10^P >= x 的最小正整数。"""
    p = 0
    v = 1
    while v < x:
        p += 1
        v *= 10
    return p

def solve():
    data = sys.stdin.buffer.read().split()
    T = int(data[0])
    out = []
    for i in range(1, T + 1):
        N = int(data[i])
        ans = 0
        for x in range(2, N + 1):
            P = get_P(x)
            if round_to(x, P) != chain_round(x, P):
                ans += 1
        out.append(str(ans))
    sys.stdout.write('\n'.join(out) + '\n')

solve()
