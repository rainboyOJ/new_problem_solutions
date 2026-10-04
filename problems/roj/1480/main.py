#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:05
# update_at: 2026-09-30 14:05

# N 可达 8e6、Σ|文字段| 可达 1e7：用 numpy 把「母串每个位置同步沿 trie 下走」
# 的逐层扫描向量化，逐层的转移/存活/标记都是对整个位置数组的批量操作。

import sys

import numpy as np

CHARS = bytes.maketrans(b"ESWN", bytes(range(4)))  # 四象字符 -> 0..3，孩子表按 4 叉编码
PAD = 4  # 定长矩阵的填充值：不是任何真实字符，查孩子表必然落空
MAX_LEN = 100  # 题面保证每段文字长度 <= 100


def build_trie(pat: np.ndarray, plen: np.ndarray) -> tuple[np.ndarray, int]:
    """把所有文字段逐层插入 trie，返回扁平孩子表 child[节点*4+字符] 与节点总数。"""
    child = np.full(4 * (int(plen.sum()) + 1), -1, np.int32)
    node = np.zeros(plen.size, np.int32)  # 每段文字当前走到哪个节点
    born = 1                              # 根节点占 0 号
    for depth in range(1, MAX_LEN + 1):
        alive = np.nonzero(plen >= depth)[0]
        if alive.size == 0:
            break
        want = node[alive] * 4 + pat[alive, depth - 1]   # 想要的 (节点, 字符) 槽位
        fresh = np.unique(want[child[want] < 0])         # 尚无孩子的槽位去重后一次性建档
        child[fresh] = np.arange(born, born + fresh.size, dtype=np.int32)
        born += fresh.size
        node[alive] = child[want]
    return child, born


def mark_occurrence(child: np.ndarray, text: np.ndarray, total: int) -> np.ndarray:
    """母串每个位置都从根同步下走，标记哪些节点的串在母串中出现过。"""
    occ = np.zeros(total, bool)
    pos = np.arange(text.size, dtype=np.int32)  # 还活着的起点
    node = np.zeros(text.size, np.int32)        # 该起点当前匹配到的节点
    for depth in range(1, MAX_LEN + 1):
        keep = pos + depth <= text.size         # 长度 depth 的窗口伸不出母串
        pos, node = pos[keep], node[keep]
        if pos.size == 0:
            break
        step = child[node * 4 + text[pos + depth - 1]]
        live = step >= 0
        pos, node = pos[live], step[live]
        occ[node] = True                        # 走到即出现；其祖先各层必然已被同一位置标记
    return occ


def longest_prefix(child: np.ndarray, occ: np.ndarray, pat: np.ndarray, plen: np.ndarray) -> np.ndarray:
    """每段文字沿自己的 trie 路径下走，答案 = 路径上最深的「出现过」节点深度。"""
    ans = np.zeros(plen.size, np.int32)
    node = np.zeros(plen.size, np.int32)
    for depth in range(1, MAX_LEN + 1):
        alive = np.nonzero(plen >= depth)[0]
        if alive.size == 0:
            break
        node[alive] = child[node[alive] * 4 + pat[alive, depth - 1]]
        hit = occ[node[alive]]                  # occ 沿路径前缀封闭，答案就是最深命中层
        ans[alive[hit]] = depth
    return ans


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])
    text = np.frombuffer(data[2][:n].translate(CHARS), np.uint8)
    pats = data[3:3 + m]
    plen = np.array([len(p) for p in pats], np.int32)
    pat = np.full((m, MAX_LEN), PAD, np.uint8)
    for i, p in enumerate(pats):                # 每段补齐到定长，方便逐层整列取字符
        pat[i, :len(p)] = np.frombuffer(p.translate(CHARS), np.uint8)

    child, born = build_trie(pat, plen)
    occ = mark_occurrence(child, text, born)
    ans = longest_prefix(child, occ, pat, plen)
    sys.stdout.write("\n".join(map(str, ans.tolist())) + "\n")


if __name__ == "__main__":
    solve()
