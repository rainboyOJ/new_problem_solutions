#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:32
# update_at: 2026-10-02 01:32

import sys

START = 1  # 变量取值：1 = 仪式安排在婚礼开始时，0 = 安排在结束时


def to_minutes(stamp: bytes) -> int:
    """把 hh:mm 转成当天的分钟数，便于用整数比较区间。"""
    return int(stamp[:2]) * 60 + int(stamp[3:])


def to_stamp(minute: int) -> str:
    """分钟数还原成 hh:mm 输出格式。"""
    return "%02d:%02d" % (minute // 60, minute % 60)


def tarjan(graph: list[list[int]]) -> list[int]:
    """迭代式 Tarjan：返回每个点的强连通分量编号（按出栈先后递增）。

    2-SAT 只需要"两点是否同分量"和分量之间的相对顺序，所以编号取弹栈顺序即可，
    缩点后的拓扑序恰好与编号顺序相反。递归深度可达 2N，这里用显式栈避免爆栈。
    """
    size = len(graph)
    index = [0] * size      # 0 表示尚未访问，否则是访问时间戳
    low = [0] * size
    comp = [-1] * size
    on_stack = bytearray(size)
    stack: list[int] = []
    timer = 0
    groups = 0

    for root in range(size):
        if index[root]:
            continue
        work = [(root, 0)]  # (当前点, 下一个待访问的邻居下标)
        while work:
            node, pos = work[-1]
            if pos == 0:  # 第一次进入这个点
                timer += 1
                index[node] = low[node] = timer
                stack.append(node)
                on_stack[node] = 1
            descended = False
            while pos < len(graph[node]):
                nxt = graph[node][pos]
                pos += 1
                if index[nxt] == 0:
                    work[-1] = (node, pos)  # 记下进度，回来时从这个邻居继续
                    work.append((nxt, 0))
                    descended = True
                    break
                if on_stack[nxt] and index[nxt] < low[node]:
                    low[node] = index[nxt]  # 反向边：用时间戳更新 low
            if descended:
                continue
            if low[node] == index[node]:  # 这个点是所在分量的根，弹栈收拢整块
                while True:
                    top = stack.pop()
                    on_stack[top] = 0
                    comp[top] = groups
                    if top == node:
                        break
                groups += 1
            work.pop()
            if work:  # 回溯：子节点的 low 可以传回父节点
                parent = work[-1][0]
                if low[node] < low[parent]:
                    low[parent] = low[node]
    return comp


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))

    # 第 i 对情侣的两段候选仪式：selected 用取值 1/0 区分开始段 与 结束段。
    trip = [(to_minutes(next(data)), to_minutes(next(data)),
             int(next(data))) for _ in range(n)]
    begin = [(s, s + d) for s, t, d in trip]  # 取值 1：S_i ~ S_i+D_i
    finish = [(t - d, t) for s, t, d in trip]  # 取值 0：T_i-D_i ~ T_i

    # 文字点 2i+v 表示"第 i 对情侣取值为 v"，它的否定是 2i+(1-v)。
    # 两对情侣的四组取值中，只要两段仪式真的重叠，这组取值就不允许：
    # 否定它得到子句，蕴涵边按 (u -> v) 与 (¬v -> ¬u) 两条成对添加。
    size = 2 * n
    graph: list[list[int]] = [[] for _ in range(size)]
    for i in range(n):
        for j in range(i + 1, n):
            for vi, oi in ((START, begin[i]), (0, finish[i])):
                a1, b1 = oi
                for vj, oj in ((START, begin[j]), (0, finish[j])):
                    a2, b2 = oj
                    if a1 < b2 and a2 < b1:  # 半开区间重叠判据：左端点严格小于对方右端点
                        graph[2 * i + vi].append(2 * j + 1 - vj)
                        graph[2 * j + vj].append(2 * i + 1 - vi)

    comp = tarjan(graph)

    out: list[str] = []
    for i in range(n):
        if comp[2 * i] == comp[2 * i + 1]:  # x 与 ¬x 同分量：无解
            out.append("NO")
            break
        # 分量编号是弹栈顺序，编号小的一侧在缩点图里更靠后，取它即得合法赋值。
        chosen = START if comp[2 * i + START] < comp[2 * i] else 0
        a, b = (begin[i] if chosen == START else finish[i])
        out.append(f"{to_stamp(a)} {to_stamp(b)}")
    else:
        out.insert(0, "YES")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
