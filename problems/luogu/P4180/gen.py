#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 20:15
# update_at: 2026-10-21 20:15
# gen.py：P4180 严格次小生成树 对拍数据生成器。
# 关键设计：权值从很小的池子里抽（大量重复权值），重复权值正是触发
# 「路径最大 == 非树边权 → 必须退到严格次大」逻辑的关键场景。
# 另外保底一条「权值特别大的弦」，保证严格次小生成树一定存在（题面数据保证存在）。

import random


def main() -> None:
    n = random.randint(3, 8)  # n>=3：保证能放保底弦，严格次小生成树必存在
    m = random.randint(n - 1, n * (n - 1) // 2)  # 连通至少要 n-1 条

    # 权值池：小池子 + 高重复概率，偶尔掺 0 权边
    pool = [random.choice([0, 1, 2, 3]) for _ in range(random.randint(1, 4))]

    # 先铺一条链保证连通（链边也用池权值）
    lines = [(i, i + 1, random.choice(pool)) for i in range(1, n)]

    # 再随机补 (m - 链长) 条边：包含重边、自环（题面允许自环）
    extra_cnt = m - (n - 1)
    seen = {(min(u, v), max(u, v)) for u, v, _ in lines}
    while len(lines) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        lines.append((u, v, random.choice(pool)))
        if u == v:
            continue  # 自环直接保留，不登记，允许出多条自环/重边
        if (min(u, v), max(u, v)) in seen:
            continue  # 重边直接保留

    # 保底大权值弦：两端的树上距离若为 1 也没关系，重复场景本身也值得测；
    # 用一个远大于池子的权值，确保存在严格更大的生成树。
    if n >= 3:
        a, b = 1, random.randint(3, n)
        lines.append((a, b, max(pool) + random.randint(1, 5)))

    random.shuffle(lines)

    print(n, len(lines))
    for u, v, w in lines:
        print(u, v, w)


if __name__ == "__main__":
    main()
