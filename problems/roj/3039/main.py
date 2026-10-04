#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:55
# update_at: 2026-10-01 11:55

# 30 万的后缀数组，纯 Python 的倍增排序每轮都要自己搬 30 万个元素，代价太高；
# 每一轮「排序 + 重排名」正好是两次全数组操作，交给 numpy 做向量化最划算。
# 排名和下标的取值范围都小于 2^31，统一用 int32，levels 表能省一半内存。

import sys

import numpy as np

END = -1  # 后缀末尾的哨兵排名：比任何真实字符都小，越界部分自动排到最短后缀之后


def suffix_array(s: bytes, length: int) -> tuple[np.ndarray, list[np.ndarray]]:
    """倍增求后缀数组：返回 (SA, levels)，其中 levels[k][i] 是子串 s[i:i+2^k] 的排名。

    每轮把「按长度 2^k 前缀排名」升级成「按长度 2^{k+1} 前缀排名」：把每个后缀的排名
    拆成 (前半段, 后半段) 两个关键字重新排序。后半段越界时读哨兵，于是所有短后缀
    在字典序里天然排在长后缀之前。
    """
    rank = np.empty(length + 1, dtype=np.int32)         # 末位留给下标 length 的哨兵
    rank[:length] = np.frombuffer(s, dtype=np.uint8)    # 长度 1 的前缀就是单个字符
    rank[length] = END
    sa = np.arange(length, dtype=np.int32)
    levels = [rank]
    step = 1                                            # 已经排好的前缀长度 2^k
    while step < length:
        second = rank[np.minimum(sa + step, length)]    # 后半段排名，越界取哨兵
        order = np.lexsort((second, rank[sa]))          # rank[sa] 是主关键字，second 是次关键字
        sa = sa[order]
        head, tail = rank[sa], second[order]
        differs = (head[1:] != head[:-1]) | (tail[1:] != tail[:-1])
        merged = np.concatenate((np.zeros(1, dtype=np.int32), np.cumsum(differs, dtype=np.int32)))
        rank = np.empty(length + 1, dtype=np.int32)     # 新排名仍按下标存放
        rank[sa] = merged                               # 合并后的次序是「排名第 i 小的下标」
        rank[length] = END
        levels.append(rank)
        if merged[-1] == length - 1:                    # 最大合并排名 = length-1 说明后缀顺序已唯一
            break
        step <<= 1
    return sa, levels


def lcp_array(sa: np.ndarray, levels: list[np.ndarray]) -> np.ndarray:
    """相邻后缀的最长公共前缀长度，即 Height 数组，返回值第 0 位固定为 0。

    字典序相邻的两个后缀，设它们起点为 lo < hi：它们的公共前缀长度可以按 2 的幂
    从大到小拼出来——只要「从当前长度再往后 2^k 个字符」这一段在 levels 表里排名
    相同，就说明这一段确实相等，可以放心把 2^k 加进答案。
    """
    lo, hi = np.minimum(sa[:-1], sa[1:]), np.maximum(sa[:-1], sa[1:])
    height = np.zeros(len(lo), dtype=np.int32)
    for k in range(len(levels) - 1, -1, -1):
        hit = levels[k][lo + height] == levels[k][hi + height]
        height += np.where(hit, 1 << k, 0)
    return np.concatenate((np.zeros(1, dtype=np.int32), height))


def solve() -> None:
    s = sys.stdin.buffer.read().strip()                 # 题目保证只有小写字母，strip 掉末尾换行即可
    sa, levels = suffix_array(s, len(s))
    height = lcp_array(sa, levels)
    del levels                                          # 倍增过程的排名表只给 LCP 用，输出前释放
    write = sys.stdout.write
    for arr in (sa, height):
        write(' '.join(map(str, arr.tolist())))
        write('\n')


if __name__ == "__main__":
    solve()
