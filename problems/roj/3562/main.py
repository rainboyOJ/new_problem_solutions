from functools import cache


def solve(n: int, m: int) -> int:
    """f(i, j)：传 i 次后球在 j 号手里的方案数，邻居环上取模。"""
    @cache
    def f(i: int, j: int) -> int:
        if i == 0:
            return j == 0  # 开始时球在 1 号（下标 0）手里
        return f(i - 1, (j - 1) % n) + f(i - 1, (j + 1) % n)  # 一次只能从左右邻居传来
    return f(m, 0)


n, m = map(int, input().split())
print(solve(n, m))
