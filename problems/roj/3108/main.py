"""食物链：带权并查集（模 3 关系）一次扫描判定每句话真假。"""
import sys


def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    fa = list(range(n + 1))   # fa[i]: i 的父节点
    d = [0] * (n + 1)         # d[i]: i 对根的关系，0同类 / 1 i吃根 / 2 根吃i（模 3 环）
    ans = 0

    def find(x: int) -> int:
        """两遍迭代：先找根，再自根向叶重压路径上的 d 为对根的关系。"""
        r = x
        while fa[r] != r:
            r = fa[r]
        path = []
        while x != r:
            path.append(x)
            x = fa[x]
        acc = 0
        for v in reversed(path):      # 根的子节点先算，边向上边累加
            acc = (acc + d[v]) % 3
            d[v], fa[v] = acc, r
        return r

    for _ in range(k):
        op, x, y = next(data), next(data), next(data)
        r = op - 1           # op=1 同类 r=0；op=2 x吃y r=1（关系环上 x→y 的距离）
        if x > n or y > n:    # 假话条件 2：编号越界
            ans += 1
            continue
        fx, fy = find(x), find(y)
        if fx == fy:          # 已有关系：核对 (d[x]-d[y]) mod 3 是否等于 r
            if (d[x] - d[y] - r) % 3:
                ans += 1      # 与前面真话冲突（含 x 吃 x）
        else:                 # 无矛盾则合并：x→根 = x→y + y→根
            fa[fx] = fy
            d[fx] = (r + d[y] - d[x]) % 3
    print(ans)


main()
