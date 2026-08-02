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


def get_overlap(left, right):
    """
    用 KMP 求 left 后缀与 right 前缀的最长重叠长度。

    把 right 当模式串，在 left 上走一遍自动机，
    扫描结束后 j 就是最长重叠长度。
    调用前保证 right 不在 left 内部，所以 j 永远不会到达 len(right)。
    """
    if not right:
        return 0
    pi = build_prefix(right)
    j = 0  # KMP 自动机的当前状态
    for ch in left:
        while j > 0 and ch != right[j]:
            j = pi[j - 1]
        if ch == right[j]:
            j += 1
    return j


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
