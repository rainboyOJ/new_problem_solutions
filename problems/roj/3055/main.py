#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:28
# update_at: 2026-10-01 12:28

import sys

END = "\x00"  # 哨兵字符：拼在号码末尾，表示“某个号码在此终止”


def is_prefix_free(numbers: list[str]) -> bool:
    """号码集合里是否两两互不为前缀（一个都不出现在另一个开头）。"""
    sons: list[dict[str, int]] = [{}]  # sons[i]：第 i 个节点的子节点表，字符 → 节点编号
    for number in numbers:
        node = 0
        for ch in number + END:  # 补一个终止哨兵，让“前缀”也拥有自己的终点
            if ch == END and sons[node]:  # 最后一位仍有后继 → 当前号码是更早号码的前缀
                return False
            son = sons[node].get(ch)
            if son is None:  # 惰性建点：先在父节点登记，再追加节点本身，编号才不会越过列表末尾
                son = sons[node][ch] = len(sons)
                sons.append({})
            elif END in sons[son]:  # 已有号码在这位终止 → 它是当前号码的前缀
                return False
            node = son
    return True


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    t = int(next(data))

    for _ in range(t):
        n = int(next(data))
        numbers = [next(data).decode() for _ in range(n)]
        verdict = "YES" if is_prefix_free(numbers) else "NO"  # 兼容 = 无前缀关系
        out.append(verdict)

    print("\n".join(out))


if __name__ == "__main__":
    solve()
