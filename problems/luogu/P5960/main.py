# 差分约束：把 x_v - x_u <= w 统一成边 u -> v 权 w，跑单源最短路判可行性、求差值上界。
# 点编号 1..n。add_leq / add_geq / add_eq 只负责统一不等号方向，不检查输入。
# 边权可正可负，所以用 SPFA；出现负环表示约束矛盾。
# Python 的 int 是任意精度，不必像 C++ 那样在相加前判溢出。
# 模板来源：rbook 代码模板 diff-constraints-py（差分约束的建边、全局可行性与单源最短路）。

import sys
from collections import deque

INF = 1 << 62  # 哨兵，比任何合法差值都大

type WeightedAdj = list[list[tuple[int, int]]]  # graph[u]：若干 (终点 v, 边权 w)


class DiffConstraints:
    """graph 与 dis 都按 1..n 编号；dis 的含义由最后一次调用决定。"""

    n: int
    graph: WeightedAdj
    dis: list[int]
    cnt: list[int]  # 当前 dis 对应的路径边数，达到 n 说明绕出了环

    def __init__(self, n: int) -> None:
        self.n = n
        self.graph = [[] for _ in range(n + 1)]
        self.dis = [0] * (n + 1)
        self.cnt = [0] * (n + 1)

    def add_leq(self, u: int, v: int, w: int) -> None:
        """约束 x_v - x_u <= w，也就是 x_v <= x_u + w。"""
        self.graph[u].append((v, w))

    def add_geq(self, u: int, v: int, w: int) -> None:
        """约束 x_u - x_v >= w，也就是 x_v <= x_u - w。"""
        self.graph[u].append((v, -w))

    def add_eq(self, u: int, v: int) -> None:
        """约束 x_u == x_v，拆成两个方向的 0 权边。"""
        self.add_leq(u, v, 0)
        self.add_leq(v, u, 0)

    def feasible(self) -> bool:
        """全局可行性：所有点距离取 0 并全部入队，等价于加一个 0 权超级源点。"""
        self.dis = [0] * (self.n + 1)
        self.cnt = [0] * (self.n + 1)
        in_queue = [True] * (self.n + 1)
        q = deque(range(1, self.n + 1))

        while q:
            u = q.popleft()
            in_queue[u] = False
            for v, w in self.graph[u]:
                if self.dis[u] + w >= self.dis[v]:
                    continue  # 这条边给不出更紧的上界
                self.dis[v] = self.dis[u] + w
                self.cnt[v] = self.cnt[u] + 1
                if self.cnt[v] >= self.n:
                    return False  # 更短的路用了至少 n 条边，必然有负环
                if not in_queue[v]:
                    q.append(v)
                    in_queue[v] = True

        return True


def main() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m = data[0], data[1]
    dc = DiffConstraints(n)
    for i in range(m):
        c, c2, y = data[2 + 3 * i], data[3 + 3 * i], data[4 + 3 * i]
        # x_c - x_c' <= y  <=>  x_c <= x_c' + y，于是建边 c' -> c 权 y
        dc.add_leq(c2, c, y)

    if not dc.feasible():
        print("NO")
        return
    print(*dc.dis[1:])


if __name__ == "__main__":
    main()
