#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:53
# update_at: 2026-10-08 07:53

import sys

GONE = -1  # 双向链表哨兵：这一侧已经没有未处理的顶点


def right_chain(px: list[int], py: list[int]) -> list[int]:
    """right[i]：从 P_i 向右张望看到的最高山顶（右侧斜率单调链的终点）。

    向右能看到的点，视线斜率必然严格递增（共线的中间点也算挡住），所以终点就是
    「斜率最大的那个可见点」；链上带路径压缩地跳跃，摊还 O(1)，不必存整条链。
    """
    n = len(px)
    right = [i + 1 for i in range(n)]
    right[n - 1] = n - 1
    for i in range(n - 3, -1, -1):
        while right[i] != n - 1:
            j, k = right[i], right[right[i]]  # 待比较的两条视线共用左端点 i
            # k 更陡（slope(i,j) < slope(i,k)）说明 j 挡不住它，可以再往右挪一步
            steeper = (py[j] - py[i]) * (px[k] - px[i]) < (py[k] - py[i]) * (px[j] - px[i])
            if steeper:
                right[i] = k
            else:
                break  # 斜率不再增大：被挡或共线，就停在这里
    return right


def left_chain(px: list[int], py: list[int]) -> list[int]:
    """left[i]：从 P_i 向左张望看到的最高山顶（左侧斜率单调链的终点）。

    向左时链的两端共享右端点 i，直接比较同一观察点 i 看到 p 与 q 的斜率。
    """
    n = len(px)
    left = [i - 1 for i in range(n)]
    left[0] = 0
    for i in range(2, n):
        while left[i] != 0:
            p, q = left[left[i]], left[i]
            # p 更远更陡（slope(p,i) < slope(q,i)）说明 q 挡不住它，继续往左跳
            steeper = (py[i] - py[p]) * (px[i] - px[q]) < (py[i] - py[q]) * (px[i] - px[p])
            if steeper:
                left[i] = p
            else:
                break
    return left


def climb(px: list[int], py: list[int]) -> list[int]:
    """每个起点的总步数：先求张望目标，再建跳跃树，最后沿树累加边权。"""
    n = len(px)
    left, right = left_chain(px, py), right_chain(px, py)
    # 张望目标：两侧各只给出一个候选（链端），再把自己算进去 —— 都比自己低时原地不动。
    # 比较键是 (y, x)：y 大者更高，y 相同取 x 大者。
    seen = [max(left[i], right[i], i, key=lambda t: (py[t], px[t])) for i in range(n)]
    root = max(range(n), key=lambda t: (py[t], px[t]))  # 全局最高山顶 = 跳跃树的根

    # 朝目标走的过程中不会掉头、目标也不会变，直到碰上第一个「目标键」更大的点。把点按
    # (y, x, 编号) 升序摘掉，则「朝目标那一侧的最近未处理邻居」正是这段直路的终点。
    order = sorted(
        (i for i in range(n) if i != root),
        key=lambda i: (py[seen[i]], px[seen[i]], i),  # 「我的目标有多高」+ 编号兜底
    )
    up = [i - 1 for i in range(n)]
    dn = [i + 1 for i in range(n)]
    up[0] = dn[n - 1] = GONE
    parent = [0] * n
    for i in order:
        parent[i] = up[i] if seen[i] < i else dn[i]
        if up[i] != GONE:
            dn[up[i]] = dn[i]
        if dn[i] != GONE:
            up[dn[i]] = up[i]

    # 终点的键严格大于自己的键，所以摘点顺序一定把父节点排在子节点之后，逆序累加即可
    ans = [0] * n
    for i in reversed(order):
        p = parent[i]
        ans[i] = ans[p] + (i - p if i > p else p - i)
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    px = [0] * n
    py = [0] * n
    for i in range(n):
        px[i], py[i] = next(data), next(data)
    print('\n'.join(map(str, climb(px, py))))


if __name__ == "__main__":
    solve()
