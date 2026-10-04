"""
关押罪犯（ROJ 3122）：扩展域并查集，按怨气值从大到小处理边。

核心：二分图判定思想 —— "不能同狱"的关系要拆到两个集合里。
把每个罪犯 i 拆成 i(第一监狱域) 和 i+n(第二监狱域)。
怨气值降序处理每条仇恨边 (a,b,c)：
- 若 find(a) == find(b)：a、b 被迫同狱，c 就是答案（更大的 c 都已合法分配）。
- 否则合并 find(a)~find(b+n)、find(b)~find(a+n)（a、b 分居两狱）。
"""
import sys


def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    # 仇恨边列表，怨气值降序
    edges = sorted(((next(data), next(data), next(data)) for _ in range(m)), key=lambda e: -e[2])

    # 扩展域：1..n 为第一监狱域，n+1..2n 为第二监狱域
    fa = list(range(2 * n + 1))

    def find(x: int) -> int:
        while fa[x] != x:
            fa[x] = fa[fa[x]]  # 路径减半
            x = fa[x]
        return x

    for a, b, c in edges:
        ra, rb = find(a), find(b)
        if ra == rb:  # 冲突不可避免，c 即市长看到的最小最大值
            print(c)
            return
        fa[ra] = find(b + n)  # a 与 b+n 同盟 => a、b 分居两狱
        fa[rb] = find(a + n)
    print(0)  # 所有仇恨都能化解


main()
