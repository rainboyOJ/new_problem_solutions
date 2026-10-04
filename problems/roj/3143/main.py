#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:27
# update_at: 2026-10-01 20:27

import sys
from collections.abc import Iterator


def read_ints(raw: str) -> Iterator[int]:
    """切出全部整数：官方数据每行尾部带 `//` 说明，先按行去掉注释再分词。"""
    for line in raw.splitlines():
        yield from map(int, line.split("//")[0].split())


def build(p: list[int], d: list[int], m: int) -> list[dict[int, tuple[int, int]]]:
    """逐人做 01 背包：layers[j][diff] = (总分和 P+D, 成员位掩码)，diff = D-P。"""
    # 并列最优时打印哪一组由扫描顺序决定，按 |d-p| 降序先处理分歧大的候选人
    order = sorted(range(len(p)), key=lambda i: -abs(d[i] - p[i]))
    layers: list[dict[int, tuple[int, int]]] = [{}]
    for i in order:
        delta, total, bit = d[i] - p[i], d[i] + p[i], 1 << i
        if len(layers) <= m:
            layers.append({})
        # j 从大到小：本层只读上一层，保证同一个人不会被选两次
        for j in range(len(layers) - 1, 1, -1):
            layer, prev = layers[j], layers[j - 1]
            for diff, (value, mask) in prev.items():
                nxt = layer.get(diff + delta)
                if nxt is None or value + total > nxt[0]:
                    layer[diff + delta] = (value + total, mask | bit)
        # 单人状态最后写：否则它会被上面的循环再叠一个人，变成两人一组
        layer = layers[1]
        nxt = layer.get(delta)
        if nxt is None or total > nxt[0]:
            layer[delta] = (total, bit)
    return layers


def solve() -> None:
    data = read_ints(sys.stdin.buffer.read().decode())
    blocks: list[str] = []
    case = 0

    while True:
        n, m = next(data), next(data)
        if n == 0 and m == 0:
            break
        case += 1

        scores = [next(data) for _ in range(2 * n)]  # 每人两个分值，按控方、辩方交替给出
        p, d = scores[::2], scores[1::2]

        layers = build(p, d, m)
        # 目标：|D-P| 最小，并列时 P+D 最大；diff 就是 D-P，故按 (|diff|, -总分和) 取最优
        best = min(layers[m], key=lambda t: (abs(t), -layers[m][t][0]))
        total, mask = layers[m][best]
        chosen = [i + 1 for i in range(n) if mask >> i & 1]
        prosecution = sum(p[i - 1] for i in chosen)

        blocks.append(
            f"Jury #{case}\n"
            f"Best jury has value {prosecution} for prosecution "
            f"and value {total - prosecution} for defence:\n"
            + " " + " ".join(map(str, chosen))
        )

    print("\n\n".join(blocks))


if __name__ == "__main__":
    solve()
