#!/usr/bin/env python3
from collections import deque
import sys


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)

    n = int(next(it))
    m = int(next(it))
    s = next(it)

    g = [[] for _ in range(n + 1)]
    in_deg = [0] * (n + 1)

    for _ in range(m):
        u = int(next(it))
        v = int(next(it))
        g[u].append(v)
        in_deg[v] += 1

    # dp[u][c] 记录以节点 u 结尾的路径中，字母 c 出现的最大频次
    dp = [[0] * 26 for _ in range(n + 1)]
    q = deque()

    for i in range(1, n + 1):
        dp[i][ord(s[i - 1]) - 97] = 1
        if in_deg[i] == 0:
            q.append(i)

    visited_cnt = 0
    ans = 0

    while q:
        u = q.popleft()
        visited_cnt += 1
        dp_u = dp[u]

        for v in g[u]:
            v_char = ord(s[v - 1]) - 97
            dp_v = dp[v]
            for c in range(26):
                val = dp_u[c] + (1 if c == v_char else 0)
                if val > dp_v[c]:
                    dp_v[c] = val

            in_deg[v] -= 1
            if in_deg[v] == 0:
                q.append(v)

    if visited_cnt < n:
        print(-1)
    else:
        print(max(max(row) for row in dp[1:]))


if __name__ == "__main__":
    solve()
