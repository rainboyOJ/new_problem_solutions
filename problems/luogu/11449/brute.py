# brute.py：小数据暴力解，模拟 Bessie 舍入和 Elsie 链式舍入，逐个数检查。
import sys
from functools import reduce

# ==========================================
# 原始写法：按题目描述，提取数位，直观易懂
# ==========================================
def round_to_original(a, b):
    """Bessie 舍入原始版本：将 a 四舍五入到最接近的 10^b。"""
    # 提取第 b 位数字（从右往左）
    digit = (a // (10 ** (b - 1))) % 10
    if digit >= 5:
        a += 10 ** b
    # 把最低的 b 位全部置 0
    a = (a // (10 ** b)) * (10 ** b)
    return a

def chain_round_original(a, b):
    """Elsie 链式舍入原始版本：先舍入到 10^1，再 10^2，...，直到 10^b。"""
    for i in range(1, b + 1):
        a = round_to_original(a, i)
    return a

# ==========================================
# Pythonic 写法：数学简化 + 高阶函数
# ==========================================
def round_to_pythonic(a, b):
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
    return reduce(round_to_pythonic, range(1, b + 1), a)

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
            # 在这里，我们可以自由切换原始写法或 Pythonic 写法进行验证
            if round_to_original(x, P) != chain_round_original(x, P):
                ans += 1
        out.append(str(ans))
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()
