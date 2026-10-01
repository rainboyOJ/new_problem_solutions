import sys
from collections import deque


def main() -> None:
    data = sys.stdin.buffer.read().split()
    n, m, t = int(data[0]), int(data[1]), int(data[2])
    forb = {(int(data[3 + 2 * i]) - 1, int(data[4 + 2 * i]) - 1) for i in range(t)}

    # 車攻击整行整列且不被空格阻挡：第 i 行的车与第 j 列的位置一一对应，
    # 每个非禁格 (i,j) 是一条边，放車两两不共行共列 <=> 二分图最大匹配
    adj: list[list[int]] = [[] for _ in range(n)]
    for x, y in forb:
        pass
    ok: list[list[bool]] = [[True] * m for _ in range(n)]
    for x, y in forb:
        ok[x][y] = False
    for i in range(n):
        adj[i] = [j for j in range(m) if ok[i][j]]

    # Hopcroft-Karp 二分图最大匹配，O(E*sqrt(V))
    matchL = [-1] * n
    matchR = [-1] * m
    ans = 0
    INF = 1 << 30
    sys.setrecursionlimit(1 << 20)
    while True:
        dist = [INF] * n
        q = deque(u for u in range(n) if matchL[u] == -1)  # 未匹配左点分层
        for u in q:
            dist[u] = 0
        found = False
        while q:
            u = q.popleft()
            for v in adj[u]:
                w = matchR[v]
                if w == -1:
                    found = True  # 到达未匹配右点，存在增广路
                elif dist[w] == INF:
                    dist[w] = dist[u] + 1
                    q.append(w)
        if not found:
            break

        def dfs(u: int) -> bool:
            for v in adj[u]:
                w = matchR[v]
                if w == -1 or (dist[w] == dist[u] + 1 and dfs(w)):
                    matchL[u], matchR[v] = v, u
                    return True
            dist[u] = INF  # 本轮失败，剪枝
            return False

        ans += sum(dfs(u) for u in range(n) if matchL[u] == -1)
    print(ans)


main()
