#!/usr/bin/env python3
"""brute.py：P4592 小数据暴力，递归收集目标节点后逐个异或取最大值。"""
import sys


def main():
    input = sys.stdin.readline
    n, q = map(int, input().split())
    w = [0] + list(map(int, input().split()))
    g = [[] for _ in range(n + 1)]
    # 一行版：append 返回 None，用 or 链式执行第二个 append（每次迭代解包一个新的 map）
    # [g[u].append(v) or g[v].append(u) for _ in range(n - 1) for u, v in [map(int, input().split())]]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        g[u].append(v)
        g[v].append(u)

    ns = []  # 当前查询的目标节点

    par = [0] * (n + 1)  # 父节点
    order = [1]
    # 一行版：setdefault 首次设置返回 u，回父边返回旧值被自动过滤（依赖树无环 + par[1]=0）
    # [order.append(v) for u in order for v in g[u] if par.setdefault(v, u) == u]
    for u in order:
        for v in g[u]:
            if v != par[u]:
                par[v] = u
                order.append(v)

    # 一行版 collect：lambda 返回 (append, 列表推导) 元组，递归时名字已绑定
    # collect = lambda u, f: (ns.append(u), [collect(v, u) for v in g[u] if v != f])
    def collect(u, f):  # 收集子树：从 u 出发不经过父 f
        ns.append(u)
        for v in g[u]:
            if v != f:
                collect(v, u)

    def path(u, target, f):  # 找 u 到 target 的路径，找到返回 True
        ns.append(u)
        if u == target:
            return True
        for v in g[u]:
            if v != f and path(v, target, u):
                return True
        ns.pop()  # 回溯

    out = []
    for _ in range(q):
        a = list(map(int, input().split()))
        ns.clear()
        if a[0] == 1:
            _, x, z = a
            collect(x, par[x])
        else:
            _, x, y, z = a
            path(x, y, 0)
        out.append(str(max(w[u] ^ z for u in ns)))  # 逐个异或取最大
    print("\n".join(out))


if __name__ == "__main__":
    main()
