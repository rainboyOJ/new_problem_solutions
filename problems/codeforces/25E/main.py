import sys
from itertools import permutations


def build_prefix(s):
    """计算 KMP 前缀函数（border 数组）"""
    n = len(s)
    pi = [0] * n
    j = 0
    for i in range(1, n):
        # 沿 border 链回退，直到前缀可扩展或到根
        while j > 0 and s[i] != s[j]:
            j = pi[j - 1]
        if s[i] == s[j]:
            j += 1
        pi[i] = j
    return pi


def get_overlap_concat(left, right):
    """
    求 left 后缀与 right 前缀的最长重叠长度 —— 版本1：拼串法。

    对 right + '#' + left 求前缀函数。'#' 不在字母表中，border 不能跨过它，
    所以整串的最长 border 恰好是 "right 的前缀 = left 的后缀"，
    最后一个 pi 值就是重叠长度。
    时间 O(|left|+|right|)，空间 O(|left|+|right|)（要存整串的 pi）。
    """
    pi = build_prefix(right + "#" + left)
    return pi[-1]


def get_overlap_automaton(left, right):
    """
    求 left 后缀与 right 前缀的最长重叠长度 —— 版本2：自动机游走法。

    把 right 当模式串，在 left 上走一遍 KMP 自动机，
    扫描结束时 j 就是最长重叠长度，与拼串法结果完全相同。
    时间 O(|left|+|right|)，空间 O(|right|)（只需存 right 的 pi）。
    调用前保证 right 不在 left 内部，所以 j 永远不会到达 len(right)。
    """
    if not right:
        return 0
    pi = build_prefix(right)
    j = 0  # KMP 自动机的当前状态 = 已匹配的 right 前缀长度
    for ch in left:
        while j > 0 and ch != right[j]:
            j = pi[j - 1]
        if ch == right[j]:
            j += 1
    return j


# 两种写法等价，二选一即可；这里用拼串法，与 index.md 的思路叙述一致
get_overlap = get_overlap_concat


def merge(left, right):
    """
    合并两个串：left 在前，right 在后，
    利用后缀-前缀重叠去掉重复部分，得到包含两者的最短串。
    """
    # 如果其中一个已经包含另一个，直接返回较长的
    if right in left:
        return left
    if left in right:
        return right
    overlap = get_overlap(left, right)
    return left + right[overlap:]


def solve():
    strings = sys.stdin.read().split()
    # 三串的合并顺序有 6 种排列，取最短结果
    answer = min(
        len(merge(merge(a, b), c))
        for a, b, c in permutations(strings)
    )
    print(answer)


if __name__ == "__main__":
    solve()
