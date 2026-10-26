"""P4408 逃学的小孩：与 main.cpp 同一算法的 Python 版。

三次遍历求出一对直径端点与两个距离数组，再扫描一遍取答案：

    ans = 直径长 + max_u min(d(u, A), d(u, B))

复杂度和 C++ 版一致，都是 O(N)，但 Python 常数较大，在 N = 2e5 的随机树上
约 1.4 s，会超出本题时限，因此只作为阅读对照，正式主解是 main.cpp。
"""

import sys


def main():
    data = sys.stdin.buffer
    n, edges = map(int, data.readline().split())

    graph = [[] for _ in range(n + 1)]  # graph[u] 是 (邻居, 边权) 的列表
    for _ in range(edges):
        u, v, weight = map(int, data.readline().split())
        graph[u].append((v, weight))
        graph[v].append((u, weight))

    def distances(start):
        """从 start 出发遍历整棵树，返回到各点的距离数组。"""
        distance = [-1] * (n + 1)  # 用 -1 当"未访问"标记：边权可以为 0
        distance[start] = 0
        order = [start]
        for node in order:  # order 一边当队列用，一边记录遍历顺序
            for neighbor, weight in graph[node]:
                if distance[neighbor] == -1:
                    distance[neighbor] = distance[node] + weight
                    order.append(neighbor)
        return distance

    from_one = distances(1)
    # 两次最远点搜索求出一对直径端点 first 和 second。
    first = max(range(1, n + 1), key=from_one.__getitem__)
    from_first = distances(first)
    second = max(range(1, n + 1), key=from_first.__getitem__)
    from_second = distances(second)

    # 答案是「直径长 + 到两端较近距离的最大值」。
    best_extra = max(
        min(da, db) for da, db in zip(from_first[1:], from_second[1:])
    )
    print(from_first[second] + best_extra)


if __name__ == "__main__":
    main()
