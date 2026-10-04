"""[NOIP2001 普及组] 数的计算(改) —— 前缀和优化线性 DP。

设 f[i] = 首项为 i 的合法数列个数，s[i] = f[1]+...+f[i]。
数列 [i] 本身合法；其后每一段都是首项 j∈[1, i//2] 的合法数列前拼 i，
故 f[i] = 1 + s[i//2]，前缀和数组把转移压到 O(1)。
答案对 100000 取模（题目只保留 5 位）。总复杂度 O(n)。
"""
import sys


def main() -> None:
    n: int = int(sys.stdin.read())
    mod: int = 100000
    f: list[int] = [0] * (n + 1)   # f[i]：首项为 i 的合法数列个数
    s: list[int] = [0] * (n + 1)   # s[i]：f[1..i] 的前缀和（已取模）
    f[1] = s[1] = 1
    for i in range(2, n + 1):
        f[i] = (s[i // 2] + 1) % mod          # 1 表示数列 [i] 自身
        s[i] = (s[i - 1] + f[i]) % mod
    print(f[n])


if __name__ == "__main__":
    main()
