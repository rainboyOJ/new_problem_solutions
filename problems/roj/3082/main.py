#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 15:25
# update_at: 2026-10-01 15:25

import sys
from collections import deque
from collections.abc import Iterator

SIDE_STEPS = 5  # 双向 BFS 每侧最多扩展的层数，两侧合计覆盖题面的 10 步上限


def expand(source: str, rules: list[tuple[str, str]]) -> Iterator[str]:
    """把 source 中某个规则的左串替换一次，产出所有一步可达的串（可能重复）。"""
    for left, right in rules:
        at = source.find(left)
        while at != -1:
            yield source[:at] + right + source[at + len(left):]
            at = source.find(left, at + 1)  # 从下一位再找，覆盖重叠出现


def layered_bfs(queue: deque[str], dist: dict[str, int], rules: list[tuple[str, str]]) -> None:
    """把 queue 这一侧向外扩展一层：新串的距离 = 队首距离 + 1。"""
    for _ in range(len(queue)):
        source = queue.popleft()
        if dist[source] == SIDE_STEPS:  # 该侧已到层数上限，不再外扩
            continue
        for nxt in expand(source, rules):
            if nxt not in dist:
                dist[nxt] = dist[source] + 1
                queue.append(nxt)


def shortest_steps(start: str, target: str, rules: list[tuple[str, str]]) -> int | None:
    """双向 BFS：返回 A 到 B 的最少变换步数，超过 10 步则返回 None。"""
    if start == target:
        return 0
    back_rules = [(right, left) for left, right in rules]  # 反向侧要沿逆规则走
    side_rules = (rules, back_rules)
    dist = ({start: 0}, {target: 0})  # dist[side]：该侧已发现的串 → 到所属端点的步数
    queues = (deque((start,)), deque((target,)))
    for k in range(1, SIDE_STEPS + 1):
        for side in (0, 1):
            layered_bfs(queues[side], dist[side], side_rules[side])
        # 交点 s 给出一条 A→s→B 的合法路径，两侧距离之和 ≥ 答案；
        # 当和 ≤ 2k 时，最短路的中间点两侧都已在 k 层内发现，该和恰为答案
        best = min((dist[0][s] + dist[1][s]
                    for s in dist[0].keys() & dist[1].keys()), default=None)
        if best is not None and best <= 2 * k:
            return best
    return None


def solve() -> None:
    data = iter(sys.stdin.read().split())
    start = next(data)
    target = next(data)
    rules = []
    for left in data:
        right = next(data)
        rules.append((left, right))  # 变换规则
    steps = shortest_steps(start, target, rules)
    print(steps if steps is not None else "NO ANSWER!")


if __name__ == "__main__":
    solve()
