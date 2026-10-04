#!/usr/bin/env python3
"""P9248 随机数据生成器（输出到 stdout）。

题面约束：N<=60, M<=10000, C_i<=10000, K,w_i,v_i<=1e9, Max<=1e18。

对拍时暴力是 O(2^N * N^2 + C(|P|,K) * NK)，所以默认模式把规模压得很小：
  * N <= 10，M <= 20，K <= 4，w_i <= 6，v_i <= 4，C_i <= 5，Max 取小值或 1e18；
  * 生成时先跑一次暴力检查 |P|（完美集合数），太大就重生成，保证 C(|P|,K) 不大。

`--big` 模式生成贴满约束的数据（N=60、M=10000、K=1e9、Max=1e18），
用于检查正解的运行时间，不参与对拍。可选参数是「轮次」，保证各轮数据不同。
"""
import random
import sys


def brute_vstar_perf(rng, n, M, w, v, adj):
    """返回 (V*, 完美集合数, 每个完美集合的合法点集)。"""
    INF = float("inf")
    d = [[INF] * n for _ in range(n)]
    for i in range(n):
        d[i][i] = 0
    for a, b, c in adj:
        d[a][b] = min(d[a][b], c)
        d[b][a] = min(d[b][a], c)
    for k in range(n):
        for i in range(n):
            if d[i][k] == INF:
                continue
            for j in range(n):
                nd = d[i][k] + d[k][j]
                if nd < d[i][j]:
                    d[i][j] = nd
    best = -1
    perfs = []
    for mask in range(1, 1 << n):
        S = [i for i in range(n) if mask >> i & 1]
        if sum(w[i] for i in S) > M:
            continue
        ss = set(S)
        st = [S[0]]
        seen = {S[0]}
        while st:
            u = st.pop()
            for a, b, c in adj:
                for p, q in ((a, b), (b, a)):
                    if p == u and q in ss and q not in seen:
                        seen.add(q)
                        st.append(q)
        if len(seen) != len(S):
            continue
        val = sum(v[i] for i in S)
        if val > best:
            best = val
            perfs = [S]
        elif val == best:
            perfs.append(S)
    return best, len(perfs)


def gen_small(rng):
    while True:
        n = rng.randint(1, 10)
        M = rng.randint(1, 20)
        K = rng.choice([1, 1, 2, 2, 3, 4])
        Max = rng.choice([0, 1, 2, 3, 5, 10, 50, 10 ** 18])
        w = [rng.randint(1, 6) for _ in range(n)]
        v = [rng.randint(0, 4) for _ in range(n)]
        adj = []
        t = rng.random()
        if t < 0.2:
            adj = [(0, i, rng.randint(1, 5)) for i in range(1, n)]      # 星形
        elif t < 0.4:
            adj = [(i - 1, i, rng.randint(1, 5)) for i in range(1, n)]  # 链形
        else:
            for i in range(1, n):
                p = rng.randrange(i)
                adj.append((p, i, rng.randint(1, 5)))
        _, nperf = brute_vstar_perf(rng, n, M, w, v, adj)
        # 控制完美集合数，保证暴力枚举 C(|P|,K) 不大
        if K == 1 and nperf <= 40:
            break
        if K == 2 and nperf <= 18:
            break
        if K == 3 and nperf <= 12:
            break
        if K == 4 and nperf <= 10:
            break
    return n, M, K, Max, w, v, adj


def gen_big(rng):
    n, M, K, Max = 60, 10000, 10 ** 9, 10 ** 18
    w = [rng.randint(1, 10000) for _ in range(n)]
    v = [rng.randint(0, 10 ** 9) for _ in range(n)]
    adj = []
    for i in range(1, n):
        p = rng.randrange(i)
        adj.append((p, i, rng.randint(1, 10000)))
    return n, M, K, Max, w, v, adj


def main():
    args = [a for a in sys.argv[1:] if a != "--big"]
    big = "--big" in sys.argv
    round_no = int(args[0]) if args else 0
    rng = random.Random(20181000 + round_no * 1000003)

    out = []
    if big:
        n, M, K, Max, w, v, adj = gen_big(rng)
        out.append(f"{n} {M} {K} {Max}")
    else:
        # 对拍一次生成一批小测例，减少进程启动开销
        batch = []
        for _ in range(rng.randint(6, 10)):
            batch.append(gen_small(rng))
        # 输出为多个测试？P9248 是单测，所以只保留一组
        n, M, K, Max, w, v, adj = batch[0]
        out.append(f"{n} {M} {K} {Max}")
    out.append(" ".join(map(str, w)))
    out.append(" ".join(map(str, v)))
    for a, b, c in adj:
        out.append(f"{a + 1} {b + 1} {c}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
