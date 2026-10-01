"""周游加拿大: 双向扩位 DP, 两条不交单调链闭环成最长大环 — O(N^3)"""
import sys


def main() -> None:
    data: list[str] = sys.stdin.read().split()
    n, v = int(data[0]), int(data[1])
    names = data[2:2 + n]
    idx: dict[str, int] = {s: i for i, s in enumerate(names)}
    # 邻接矩阵 (城市已按自西向东编号 0..n-1)
    adj: list[list[bool]] = [[False] * n for _ in range(n)]
    pos = 2 + n
    for _ in range(v):
        a, b = idx[data[pos]], idx[data[pos + 1]]
        pos += 2
        adj[a][b] = adj[b][a] = True

    # dp[a][b] (a<=b): 去程停 a / 回程停 b, 覆盖城市数 (不含终点 n-1, 计入起点 0)
    # 合法分解要求除 0 和 n-1 外点不交, 故 a==b 的中间态无意义, 只留 dp[0][0]
    NEG = -10**9
    dp: list[list[int]] = [[NEG] * n for _ in range(n)]
    dp[0][0] = 0
    for a in range(n):
        for b in range(n):
            cur = dp[a][b]
            # 无效态 / 中途 a==b / 两条链都已抵达终点: 不再扩展
            if cur < 0 or (a == b and a != 0) or (a == n - 1 and b == n - 1):
                continue
            t = cur + 1
            row = adj[a]  # 去程前进: a -> c
            for c in range(max(a, b) + 1, n):
                if row[c] and t > dp[c][b]:
                    dp[c][b] = t
            row = adj[b]  # 回程前进: b -> c
            for c in range(b + 1, n):
                if row[c] and t > dp[c][a]:
                    dp[c][a] = t

    # 闭合: 回程停 b 且 b 与终点相邻 -> 去程已在终点, +1 补上终点本身
    best = 0
    last = adj[n - 1]
    for b in range(n - 1):
        if dp[n - 1][b] >= 0 and last[b]:
            best = max(best, dp[n - 1][b] + 1)
    print(max(best, 1))


main()
