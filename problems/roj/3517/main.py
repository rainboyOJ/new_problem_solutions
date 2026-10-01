#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:52
# update_at: 2026-10-02 04:52

import sys
from collections.abc import Iterator


def hits(s: str, sub: str) -> Iterator[int]:
    """s 中子串 sub 的所有出现起点（允许重叠出现）。"""
    i = s.find(sub)
    while i != -1:
        yield i
        i = s.find(sub, i + 1)


def step(front: dict[str, int], seen: dict[str, int], other: dict[str, int],
         rules: list[tuple[str, str]]) -> tuple[dict[str, int], list[str]]:
    """把 front 这一整层向外扩一步，返回（新的一层, 本层遇到的相遇点）。

    seen 是本方向"串 -> 到达深度"，other 是对面方向的同一张表；
    新串出现在 other 里说明两侧搜索树接上了，接上处总步数 = 两侧深度之和。
    """
    depth = max(front.values()) + 1  # 本层所有新串的深度相同
    nxt: dict[str, int] = {}
    meeting: list[str] = []
    for s in front:
        for a, b in rules:
            for i in hits(s, a):
                t = s[:i] + b + s[i + len(a):]
                if t not in seen:
                    seen[t] = depth
                    if t in other:  # 对面方向已经到过 t，这是一条相遇边
                        meeting.append(t)
                    nxt[t] = depth
    return nxt, meeting


def solve() -> None:
    words = sys.stdin.read().split()
    a, b, *pair_list = words
    rules = list(zip(pair_list[0::2], pair_list[1::2]))
    back = [(b, a) for a, b in rules]  # 反向规则：从 B 往回变

    if a == b:
        print(0)
        return

    fa: dict[str, int] = {a: 0}  # 正向当前层：串 -> 变换次数
    fb: dict[str, int] = {b: 0}  # 反向当前层
    seen_a = dict(fa)            # 各方向所有到过的串及其深度
    seen_b = dict(fb)
    for _ in range(10):          # 总步数上限 10，两侧深度之和每轮加 1
        forward = len(fa) <= len(fb)  # 总是扩展更小的一层
        if forward:
            fa, meeting = step(fa, seen_a, seen_b, rules)
            side_depth = max(seen_a.values())
        else:
            fb, meeting = step(fb, seen_b, seen_a, back)
            side_depth = max(seen_b.values())
        if meeting:  # 相遇总步数 = 本侧深度 + 对面到达各相遇点的深度，取最小
            print(min(side_depth + seen_b[t] if forward else side_depth + seen_a[t]
                      for t in meeting))
            return
        if not (fa if forward else fb):  # 这一侧扩不出新串，永远接不上了
            break
    print("NO ANSWER!")


if __name__ == "__main__":
    solve()
