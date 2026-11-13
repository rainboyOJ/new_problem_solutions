#!/usr/bin/env python3
import sys


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)

    s = next(it)
    t = next(it)

    if len(s) != len(t):
        print(-1)
        return

    n = int(next(it))
    INF = 10**15

    # 初始化 26 x 26 距离矩阵
    d = [[0 if i == j else INF for j in range(26)] for i in range(26)]

    for _ in range(n):
        u_ch = next(it)
        v_ch = next(it)
        w = int(next(it))
        u = ord(u_ch) - 97
        v = ord(v_ch) - 97
        if w < d[u][v]:
            d[u][v] = w

    # Floyd-Warshall 全源最短路
    for k in range(26):
        d_k = d[k]
        for i in range(26):
            d_i = d[i]
            d_ik = d_i[k]
            if d_ik >= INF:
                continue
            for j in range(26):
                new_dist = d_ik + d_k[j]
                if new_dist < d_i[j]:
                    d_i[j] = new_dist

    total_cost = 0
    res_chars = []

    for ch_s, ch_t in zip(s, t):
        u = ord(ch_s) - 97
        v = ord(ch_t) - 97

        best_cost = INF
        best_target = -1

        for target in range(26):
            cur_cost = d[u][target] + d[v][target]
            if cur_cost < best_cost:
                best_cost = cur_cost
                best_target = target

        if best_cost >= INF:
            print(-1)
            return

        total_cost += best_cost
        res_chars.append(chr(97 + best_target))

    print(total_cost)
    print("".join(res_chars))


if __name__ == "__main__":
    solve()
