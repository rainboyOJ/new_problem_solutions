#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 02:27
# update_at: 2026-10-02 02:36

import sys
from collections import deque

HOURS = 24      # 一天 24 个时段，前缀和数组长度为 25
SHIFT = 8       # 每人连续工作 8 小时
NEG = -(10 ** 9)  # 最长路里的“不可达”哨兵，比任何合法距离都小


def shift_ok(total: int, need: list[int], hired: list[int]) -> bool:
    """总雇佣人数恰好为 total 时，是否存在满足需求的排班。

    设 s[i] 是 0..i-1 时段开始上班人数的前缀和（s[0]=0，s[24]=total）。
    题面只给“起始人数”的计数 hired[]，所以每小时在线人数就是 8 个连续前缀和之差。
    把每条需求化成差分约束的边后，用 SPFA 判正环：有正环说明约束自相矛盾。
    """
    edges: list[list[tuple[int, int]]] = [[] for _ in range(HOURS + 1)]

    # 0 <= s[i+1]-s[i] <= hired[i]：第 i 小时上岗人数非负且不超过可用人数。
    for i in range(HOURS):
        edges[i].append((i + 1, 0))
        edges[i + 1].append((i, -hired[i]))
    # 循环变量取 i = h+1 = 8..24，即不跨零点的小时 h = 7..23：
    # 覆盖它的班次全部从 [h-7, h] 开始，故 s[h+1]-s[h-7] >= need[h]。
    for i in range(SHIFT, HOURS + 1):
        edges[i - SHIFT].append((i, need[i - 1]))
    # 循环变量取 i = h+1 = 1..7，即跨零点的小时 h = 0..6：
    # 绕回来的那段班次从上一轮的 h+17 = i+16 开始，故 s[i]-s[i+16] >= need[h]-total（把常量 total 移右）。
    for i in range(1, SHIFT):
        edges[i + 16].append((i, need[i - 1] - total))
    # 固定 s[24] = total：两条反向边把差值锁死。
    edges[0].append((HOURS, total))
    edges[HOURS].append((0, -total))

    dist = [NEG] * (HOURS + 1)
    dist[0] = 0
    relax_count = [0] * (HOURS + 1)
    in_queue = [False] * (HOURS + 1)
    in_queue[0] = True
    queue = deque([0])

    while queue:
        u = queue.popleft()
        in_queue[u] = False
        du = dist[u]
        for v, w in edges[u]:
            if du + w > dist[v]:
                dist[v] = du + w
                relax_count[v] += 1
                if relax_count[v] >= HOURS + 1:  # 松弛次数达点数即存在正环
                    return False
                if not in_queue[v]:
                    in_queue[v] = True
                    queue.append(v)
    return True


def min_cashiers(need: list[int], hired: list[int], total_applicants: int) -> int:
    """二分最少雇佣人数：可行性与雇佣人数单调相关，取下界。"""
    low, high, answer = 0, total_applicants, -1
    while low <= high:
        mid = (low + high) // 2
        if shift_ok(mid, need, hired):
            answer, high = mid, mid - 1
        else:
            low = mid + 1
    return answer


def read_case(tokens: list[bytes], pos: int) -> tuple[list[int], list[int], int]:
    """从 pos 处读一组数据，返回（每小时需求、各起始时刻申请人数、新游标）。

    只接受题面允许的合法输入：token 不够、非整数或起始时刻越界都直接判为坏数据。
    """
    need = list(map(int, tokens[pos:pos + HOURS]))  # R(0)..R(23)
    if len(need) < HOURS:
        raise ValueError
    n = int(tokens[pos + HOURS])
    starts = list(map(int, tokens[pos + HOURS + 1:pos + HOURS + 1 + n]))
    if len(starts) < n or not all(0 <= t < HOURS for t in starts):
        raise ValueError

    start_count = [0] * HOURS  # 想从第 i 小时开始上班的申请人数
    for t in starts:
        start_count[t] += 1
    return need, start_count, pos + HOURS + 1 + n


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    out: list[str] = []
    pos = 1

    for _ in range(int(tokens[0]) if tokens else 0):
        try:
            need, start_count, pos = read_case(tokens, pos)
        except (IndexError, ValueError):  # 后文格式不符，已读到的组仍照常输出
            break
        best = min_cashiers(need, start_count, sum(start_count))
        out.append("No Solution" if best < 0 else str(best))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
