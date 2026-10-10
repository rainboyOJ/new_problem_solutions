#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:44
# update_at: 2026-10-08 02:44

import sys

NEG = -(10 ** 30)  # 不可达状态哨兵：远小于任何真实得分（|总分| ≤ 10^8）


def best_score(vals: list[int], k: int, w: int) -> int:
    """一组数据（分值表 vals、k 个球、每个球宽 w）能拿到的最大总分。

    pos = n + w - 1：把右边界外补 w-1 个分值为 0 的空位，球就允许悬在右边界外；
    左边界外同理（由 q 被钳到 0 的那个分支表达）。pre 是前缀和。
    """
    n = len(vals)
    pos = n + w - 1
    pre = [0] * (pos + 1)
    total = 0
    for i in range(1, n + 1):
        total += vals[i - 1]
        pre[i] = total
    for i in range(n + 1, pos + 1):
        pre[i] = total                    # 空位不得分：前缀和保持不变

    prev_a = [NEG] * (pos + 1)            # 0 个球时「最后一个球右端点恰为 i」不可达
    prev_b = [0] * (pos + 1)              # 0 个球时「右端点都不超过 i」得分为 0
    dq = [0] * (pos + 1)                  # 单调队列（存下标），维护 key 在窗口内的最大值
    for _ in range(k):
        # 重叠转移只用到 prev_a[p] - pre[p]：把「上一球右端点 p」对分值的净贡献先算好
        key = [prev_a[p] - pre[p] for p in range(pos + 1)]
        cur_a = [NEG] * (pos + 1)
        cur_b = [0] * (pos + 1)
        head = tail = 0
        running = 0                       # cur_b[i]，B 对 i 单调不减
        for i in range(1, pos + 1):
            p = i - 1                     # 候选的「上一球右端点」逐个入队
            while tail > head and key[dq[tail - 1]] <= key[p]:
                tail -= 1                 # 队尾比新来的小，永远不会再当选
            dq[tail] = p
            tail += 1
            lo = i - w + 1                # 重叠要求上一球窗口盖到本窗口左端 i-w+1
            while head < tail and dq[head] < lo:
                head += 1
            # 情况一：与上一球重叠，本球只新增 p+1..i
            best = NEG if head >= tail else pre[i] + key[dq[head]]
            # 情况二：与上一球不重叠（q = i-w ≥ 0），或球从左边界外伸进来（钳到 q = 0，
            # 此时 1..i 整段都是新球瓶；prev_b[0] - pre[0] = 0 恰好就是「前面没有球」）
            q = i - w if i > w else 0
            cand = pre[i] + prev_b[q] - pre[q]
            if cand > best:
                best = cand
            cur_a[i] = best
            if best > running:
                running = best            # 位置 i 可打可不打
            cur_b[i] = running
        prev_a, prev_b = cur_a, cur_b
    # B 对球数单调不减，所以 B[pos][k] 就是「至多 k 个球」的答案；全负数据下它是 0
    return prev_b[pos]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    tests = next(data)

    for _ in range(tests):
        n, k, w = next(data), next(data), next(data)
        vals = [next(data) for _ in range(n)]
        out.append(str(best_score(vals, k, w)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
