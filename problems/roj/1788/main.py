#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 08:10
# update_at: 2026-10-08 08:10

import sys

type Coords = list[int]    # 一维坐标数组（x 或 y），下标就是山顶编号


def far_side(xs: Coords, ys: Coords, sgn: int) -> Coords:
    """far[i]：从 i 沿 sgn 方向（+1 向右 / -1 向左）看，斜率最大的山顶编号。

    这就是该方向能看到的最高山顶：斜率最大的点必然可见，而比它更高的点都被它挡住。
    若 far[i] 再往远处还有一个更陡的点 far[far[i]]，就顺着已算好的答案直接跳过去，
    链式跳跃（far[i] 不断替换成 far[far[i]]）让整体摊还到 O(n)。
    边界处没有更远处的点，far[i] 就是 i 自己。
    """
    n = len(xs)
    far = [min(max(i + sgn, 0), n - 1) for i in range(n)]
    for i in (range(n - 3, -1, -1) if sgn == 1 else range(2, n)):
        j = far[i]
        while True:
            k = far[j]                       # j 再往远处看的下降点
            # 乘 sgn 把"向左看"折成同一个不等式：斜率(i,j) 严格小于 斜率(i,k) 才继续跳
            steeper = (ys[k] - ys[i]) * (xs[j] - xs[i]) * sgn \
                > (ys[j] - ys[i]) * (xs[k] - xs[i]) * sgn
            if not steeper:
                break
            j = far[j]
        far[i] = j
    return far


def walk_steps(xs: Coords, ys: Coords) -> Coords:
    """ans[i]：从山顶 i 出发爬到最高山顶所需的步数。"""
    n = len(xs)
    if n == 1:
        return [0]

    hi = max(range(n), key=lambda i: (ys[i], xs[i]))   # 全局最高：y 大者，y 同取 x 大者
    rj, lj = far_side(xs, ys, 1), far_side(xs, ys, -1)

    # f[i]：i 真正能看到的最高山顶 = {i, 左侧斜率最大者, 右侧斜率最大者} 中 rank 最高的。
    # 边界只有一侧有候选；两侧都不比 i 高时 f[i] 就退回 i（即在此停住）。
    f = [hi] * n
    for i in range(n):
        if i == hi:
            continue
        f[i] = max(i, lj[i], rj[i], key=lambda p: (ys[p], xs[p]))

    fkey = [ys[f[i]] * 1000001 + xs[f[i]] for i in range(n)]  # 山顶优劣压成整数：先比 y 再比 x
    del rj, lj                        # 两侧最远可见点用完就丢，给后面的栈/链表腾内存

    # nxt[i] / prv[i]：右侧 / 左侧第一个 fkey 严格大于 fkey[i] 的山顶（单调栈 O(n)）
    # 值为 -1 表示这一侧根本没有更高的山顶
    nxt, prv = [-1] * n, [-1] * n
    st: list[int] = []
    for i in range(n - 1, -1, -1):
        while st and fkey[st[-1]] <= fkey[i]:
            st.pop()
        nxt[i] = st[-1] if st else -1
        st.append(i)
    st = []
    for i in range(n):
        while st and fkey[st[-1]] <= fkey[i]:
            st.pop()
        prv[i] = st[-1] if st else -1
        st.append(i)

    # par[i]：最优路径上 i 的下一站。朝 f[i] 走的途中只有"第一个能看得更高"的位置才会
    # 改目标，先到那里；沿途没人看得更高，就一口气走到 f[i]。
    par = [hi] * n
    for i in range(n):
        if i == hi:
            continue
        v = f[i]
        if v > i:
            k = nxt[i]
            par[i] = k if k != -1 and k < v else v
        else:
            k = prv[i]
            par[i] = k if k != -1 and k > v else v

    del fkey, nxt, prv, f             # 同上：定完 par 就不再需要这些中转数组
    # 沿 par 链递推：ans[i] = |i - par[i]| + ans[par[i]]。
    # 每条链的终点都是全局最高峰 hi，链上每个山顶的答案只会被填一次，总代价 O(n)。
    ans = [-1] * n                    # -1 表示该山顶的步数还没算出来
    ans[hi] = 0
    for i in range(n):
        if ans[i] >= 0:
            continue
        path: list[int] = []
        cur = i
        while ans[cur] < 0:            # 先沿 par 走到一个已有答案的位置
            path.append(cur)
            cur = par[cur]
        base = ans[cur]
        for v in reversed(path):       # 再倒着把路上每个山顶的步数补齐
            base += abs(v - par[v])
            ans[v] = base
    return ans


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    n = int(tokens[0])
    # 这里用切片而不是逐个数 next()：一共 10^6 个数，切片 + map(int) 全在 C 层跑，
    # 比在 Python 层调 10^6 次 next() 快约一倍（实测 0.06s vs 0.10s）。
    xs = list(map(int, tokens[1:2 * n + 1:2]))   # 奇数位是 x，x 坐标严格递增
    ys = list(map(int, tokens[2:2 * n + 1:2]))   # 偶数位是 y
    del tokens                                   # 原始 token 列表有 10^6 个 bytes 对象，尽早释放
    print('\n'.join(map(str, walk_steps(xs, ys))))


if __name__ == "__main__":
    solve()
