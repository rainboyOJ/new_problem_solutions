#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:54
# update_at: 2026-10-01 12:54

import sys


def fit_first(cats: list[int], capacity: int) -> int:
    """贪心：重的猫先来，塞进剩余空间最小、又还装得下的那辆车，返回车数。"""
    space_left: list[int] = []
    for weight in cats:
        pick, gap = -1, None  # gap 记录候选车里最小的剩余空间
        for j, space in enumerate(space_left):
            if space >= weight and (gap is None or space < gap):
                gap, pick = space, j
        if pick < 0:
            space_left.append(capacity - weight)
        else:
            space_left[pick] -= weight
    return len(space_left)


def fewest_cars(cats: list[int], capacity: int) -> int:
    """把已按重量降序排好的猫装进容量为 capacity 的车，返回最少车数。"""
    n = len(cats)
    # 贪心不保证最优，但它给出的车数一定可行，可以直接当搜索的上界
    best = fit_first(cats, capacity)
    space_left: list[int] = []  # 每辆已租车的剩余空间，车的数量就是 len(space_left)
    free = 0  # space_left 里所有空位之和

    # 下界一：第 i 只及以后是最重的几只，把它们按「每辆车都恰好装满」的最优情况
    # 摊开，车数只可能更少，所以这个值是剩余部分的车数下界。
    suffix = [0] * (n + 1)
    for i in range(n - 1, -1, -1):
        suffix[i] = suffix[i + 1] + cats[i]
    least = [1] * (n + 1)  # least[i] = 第 i 只及以后至少还要几辆车
    for i in range(n):
        for k in range(1, n - i + 1):
            # 这一组最轻的是 cats[i+k-1]，每辆车最多装 W // cats[i+k-1] 只
            group = -(-k // max(1, capacity // cats[i + k - 1]))
            if group > least[i]:
                least[i] = group

    def dfs(i: int) -> None:
        """决定第 i 只猫坐哪辆车：要么塞进某辆已租车，要么新租一辆。"""
        nonlocal best, free
        if len(space_left) >= best:  # 已租车数不优于当前最优解
            return
        if i == n:
            best = len(space_left)  # 所有猫都上车，得到一个更优解
            return
        if least[i] >= best:  # 剩下最重的这几只至少还要这么多车
            return
        # 下界二：现有空位塞不下的重量，每 capacity 必须再开一辆新车
        if len(space_left) + -(-(suffix[i] - free) // capacity) >= best:
            return
        weight = cats[i]
        tried = set()  # 剩余空间相同的车完全对称，只需要试其中一辆
        for j, space in enumerate(space_left):
            if space >= weight and space not in tried:
                tried.add(space)
                space_left[j] = space - weight
                dfs(i + 1)
                space_left[j] = space
        space_left.append(capacity - weight)  # 新租一辆车，这辆只装它一只
        free += capacity - weight
        dfs(i + 1)
        free -= space_left.pop()  # 回溯：撤掉这辆新车

    dfs(0)
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, capacity = next(data), next(data)
    # 先安排重的猫：重猫可选的落点少，尽早定下来能更快收紧 best，剪掉更多分支
    cats = sorted((next(data) for _ in range(n)), reverse=True)

    print(fewest_cars(cats, capacity))


if __name__ == "__main__":
    solve()
