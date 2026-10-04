#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:40
# update_at: 2026-10-04 09:12

import sys
from collections import defaultdict

ORZ = b"Orz YYR tql"  # 该结尾字母下凑不够第 k 名时的回答


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())  # token 流：名字与数字都按 next() 顺序消费
    n, m = int(next(data)), int(next(data))

    # 按名字结尾字母分桶：排序键 (-评分, 读入序号)，评分大在前、同分先读入在前
    buckets: dict[str, list[tuple[int, int, bytes]]] = defaultdict(list)
    for i in range(2, 2 + 2 * n, 2):
        name = next(data)
        buckets[name[-1:]].append((-int(next(data)), i, name))
    for ranked in buckets.values():
        ranked.sort()

    out: list[bytes] = []
    for j in range(2 * n, 2 * n + 2 * m, 2):
        ranked = buckets.get(next(data))  # 询问的结尾字母
        k = int(next(data))
        out.append(ranked[k - 1][2] if ranked is not None and len(ranked) >= k else ORZ)

    sys.stdout.buffer.write(b"\n".join(out) + b"\n")


if __name__ == "__main__":
    solve()
