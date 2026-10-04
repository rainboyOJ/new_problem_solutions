"""排队方案数：任意两只牡牛之间至少 K 只牝牛。O(N) DP,取模 5000011。"""
import sys

def main() -> None:
    n, k = map(int, sys.stdin.read().split())
    MOD = 5000011
    # b[i]: 长 i 且以牡牛结尾的方案数; c[i]: 以牝牛结尾; s[i]: 总方案数
    b = [0] * (n + 1)
    c = [0] * (n + 1)
    s = [0] * (n + 1)
    s[0] = 1
    for i in range(1, n + 1):
        b[i] = s[i - k - 1] if i > k else 1   # 结尾放牡牛: 上一头牡牛最远到 i-k-1,否则它是第一头
        c[i] = s[i - 1]                       # 结尾放牝牛: 任意合法前缀延长
        s[i] = (b[i] + c[i]) % MOD
    print(s[n] % MOD)

main()
