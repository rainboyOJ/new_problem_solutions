# 「一本通 1.3 例 1」数的划分：把 n 分成 k 个互不相同考虑顺序的方案数（不减划分）
# f[i][j]：把 i 分成 j 份（每份 >= 1，不减排列）的方案数
# 转移：f[i][j] = f[i-1][j-1]（第 j 份恰为 1，去掉它）+ f[i-j][j]（每份都减 1）
import sys
from functools import cache
from sys import setrecursionlimit

setrecursionlimit(100000)


@cache
def f(i: int, j: int) -> int:
    if i < j or j == 0:      # 份不够分或份数为 0
        return 0
    if j == 1:               # 只剩一份，全部给它
        return 1
    return f(i - 1, j - 1) + f(i - j, j)  # 递归展开为二维 DP


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
k = next(data)
print(f(n, k))
