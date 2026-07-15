# brute.py：小数据暴力解，模拟 Bessie 舍入和 Elsie 链式舍入，逐个数检查。
import sys
from functools import reduce

def round_to(a, b):
    """Bessie 舍入：加半取整法
    (a + 10^b // 2) // 10^b * 10^b
    """
    p = 10 ** b
    return (a + p // 2) // p * p

def chain_round_A(a, b):
    """Elsie 链式舍入（方案 A）：递推维护幂次"""
    p = 10
    for _ in range(b):
        a = (a + p // 2) // p * p
        p *= 10
    return a

def chain_round_B(a, b):
    """Elsie 链式舍入（方案 B）：函数式 reduce 写法"""
    return reduce(round_to, range(1, b + 1), a)

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
            # 这里调用方案 A
            if round_to(x, P) != chain_round_A(x, P):
                ans += 1
        out.append(str(ans))
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()
