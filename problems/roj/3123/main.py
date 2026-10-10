#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 21:00
# update_at: 2026-10-09 21:00

import sys

CAP = 2  # 方案数封顶：只关心「是否唯一」，≥2 与 2 等价


def solve() -> None:
    """扩展域（种类）并查集 + 连通块二选一背包 DP。

    yes ⇔ 询问者与被询问者同类；no ⇔ 异类。把每个人拆成天神态 x 与恶魔态 x+V，
    合并关系后每个连通块被分成互斥两侧 c0 / c1（一侧为天神）；背包统计
    凑出 p1 个天神的方案数，恰为 1 才唯一确定，0（无解）与 ≥2（多解）都输出 no。
    """
    data = sys.stdin.buffer.read().split()
    pos, out = 0, []
    while pos + 2 < len(data):
        n, p1, p2 = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        if n == 0 and p1 == 0 and p2 == 0:
            break
        V = p1 + p2
        parent = list(range(2 * V + 1))  # 1..V 天神态节点，V+1..2V 恶魔态节点

        if V == 0:  # 题面保证 x,y ≥ 1，p1+p2=0 只会出现在非法输入；
            pos += 3 * n  # 仍读完本组询问，避免多组输入错位
            out.append("end")
            continue

        def find_set(x: int) -> int:
            root = x
            while parent[root] != root:
                root = parent[root]
            while parent[x] != root:  # 路径压缩
                parent[x], x = root, parent[x]
            return root

        for _ in range(n):
            x, y, a = int(data[pos]), int(data[pos + 1]), data[pos + 2]
            pos += 3
            pairs = ((x, y), (x + V, y + V)) if a == b"yes" else ((x, y + V), (x + V, y))
            for u, v in pairs:  # yes 合并同类，no 合并异类
                ru, rv = find_set(u), find_set(v)
                if ru != rv:
                    parent[ru] = rv

        # 同一人既天神又恶魔 ⇒ 回答自相矛盾，无解
        if any(find_set(i) == find_set(i + V) for i in range(1, V + 1)):
            out.append("no")
            continue

        # 每个连通块取出一对互斥根 (r, r_op)；comp_id[根] 为该根在 comp 中的槽位
        comp_root = []
        comp_id = {}
        for i in range(1, V + 1):
            r = find_set(i)
            if r not in comp_id:
                comp_id[r] = len(comp_root)
                comp_root.append(r)
                r_op = find_set(i + V)
                comp_id[r_op] = len(comp_root)
                comp_root.append(r_op)
        comp = [[] for _ in comp_root]  # comp[2c] / comp[2c+1] 是第 c 块的两侧成员
        for i in range(1, V + 1):
            comp[comp_id[find_set(i)]].append(i)

        K = len(comp_root) // 2
        # 计数型 0/1 背包：dp[i][j] = 前 i 块中选 j 人当天的方案数（封顶 CAP）
        dp = [[0] * (p1 + 1) for _ in range(K + 1)]
        dp[0][0] = 1
        for i in range(1, K + 1):
            na, nb = len(comp[2 * (i - 1)]), len(comp[2 * (i - 1) + 1])
            prev, cur = dp[i - 1], dp[i]
            for j in range(p1 + 1):
                val = (prev[j - na] if j >= na else 0) + (prev[j - nb] if j >= nb else 0)
                cur[j] = min(CAP, val)

        if dp[K][p1] != 1:
            out.append("no")  # 0 = 无解，≥2 = 多解，都无法唯一确定身份
            continue

        # 唯一路径回溯：dp[i][cur]==1 时两侧不会同时可行
        gods, cur_j = [], p1
        for i in range(K, 0, -1):
            na, nb = len(comp[2 * (i - 1)]), len(comp[2 * (i - 1) + 1])
            if cur_j >= na and dp[i - 1][cur_j - na] == 1:
                gods.extend(comp[2 * (i - 1)])
                cur_j -= na
            else:
                gods.extend(comp[2 * (i - 1) + 1])
                cur_j -= nb
        out.extend(map(str, sorted(gods)))
        out.append("end")

    sys.stdout.write("\n".join(out) + ("\n" if out else ""))


if __name__ == "__main__":
    solve()
