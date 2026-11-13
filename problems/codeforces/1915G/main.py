#!/usr/bin/env python3
import heapq
import sys


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)

    t = int(next(it))
    out = []

    for _ in range(t):
        n = int(next(it))
        m = int(next(it))

        g = [[] for _ in range(n + 1)]
        for _ in range(m):
            u = int(next(it))
            v = int(next(it))
            w = int(next(it))
            g[u].append((v, w))
            g[v].append((u, w))

        s = [0] + [int(next(it)) for _ in range(n)]

        INF = 10**18
        dist = [[INF] * (n + 1) for _ in range(n + 1)]

        dist[1][1] = 0
        pq = [(0, 1, 1)]

        while pq:
            d, u, b = heapq.heappop(pq)
            if d > dist[u][b]:
                continue

            # 动作 1：换车下潜（耗时 0）
            if s[u] < s[b]:
                if dist[u][u] > d:
                    dist[u][u] = d
                    heapq.heappush(pq, (d, u, u))

            # 动作 2：本层平移
            cur_speed = s[b]
            for v, w in g[u]:
                cost = d + w * cur_speed
                if dist[v][b] > cost:
                    dist[v][b] = cost
                    heapq.heappush(pq, (cost, v, b))

        ans = min(dist[n][1:])
        out.append(str(ans))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
