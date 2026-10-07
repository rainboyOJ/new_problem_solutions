#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:40
# update_at: 2026-10-07 15:48

import sys
from bisect import bisect_left, bisect_right
from collections import Counter

FLIP = bytes.maketrans(b'NY', b'YN')  # 逐位取反的查表，用 bytes 比较省掉解码

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Counts = dict[bytes, int]        # 答案串 -> 写出这份答案的人数


def flip(s: bytes) -> bytes:
    """逐位取反：N 变 Y、Y 变 N，得到与 s 完全不同的串（m ≥ 1）。"""
    return s.translate(FLIP)


def pick_by_counts(cnt: Counts, p: int, q: int) -> bytes | None:
    """p + q > 0 时求标准答案：它本身出现恰 p 次，它的反串出现恰 q 次。

    每个出现过的串 x 给出两个候选：s = x（p > 0，s 自己出现过）和 s = comp(x)
    （p = 0 < q，此时 comp(s) = x 恰出现 q 次）。合法解至少让其中之一出现过，故不漏解。
    """
    cands = [s for x in cnt for s in (x, flip(x))]
    return min((s for s in cands if cnt.get(s, 0) == p and cnt.get(flip(s), 0) == q), default=None)


def smallest_free(forbid: list[bytes], m: int) -> bytes | None:
    """禁止集合之外的、长度 m 的字典序最小串；一个都不存在时返回 None。

    前缀 `pref` 之下共有 2^rem 个长度 m 的串，只有在被禁的少于这么多时才能延伸下去。
    `forbid` 已排序，以 pref 为前缀的串恰是连续一段，二分即可数出个数。
    """
    prefix = b''
    lo, hi = 0, len(forbid)          # forbid[lo:hi] 恰好是以 prefix 为前缀的那些串
    for d in range(m):
        rem = m - d - 1              # 定下这一位后还剩几位
        for ch in (b'N', b'Y'):      # 先试 N，字典序最小
            pref = prefix + ch
            nlo = bisect_left(forbid, pref, lo, hi)
            nhi = bisect_right(forbid, pref + b'Z' * rem, lo, hi)  # 'Z' 比 'N'、'Y' 都大
            blocked = nhi - nlo      # 这个前缀下被禁掉的串数
            if blocked < 1 << rem:   # 还留着不受禁的延伸，这一位就定成 ch
                prefix, lo, hi = pref, nlo, nhi
                break
        else:
            return None              # 两位都无路可走，这一层就断了
    return prefix


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m, p, q = int(next(data)), int(next(data)), int(next(data)), int(next(data))
    rows = [next(data) for _ in range(n)]

    if p or q:
        # 只需统计出现次数：满分人数与零分人数都直接读自计数表
        cnt = Counter(rows)
        ans = pick_by_counts(cnt, p, q)
    else:
        # 标准答案及其反串都不得出现，等价于避开禁止集合 A ∪ comp(A)
        forbid = sorted({flip(s) for s in rows} | set(rows))
        del rows                     # 15 MB 级输入，构造完限制集就释放
        ans = smallest_free(forbid, m)

    print(-1 if ans is None else ans.decode())


if __name__ == "__main__":
    solve()
