import sys

def min_rotation(s: str) -> str:
    """最小表示法（Lyndon / Booth 思想）：返回循环串 s 的字典序最小旋转。

    i, j 是两个候选起点，k 是当前匹配长度：
    - s[i+k] == s[j+k]：k 继续延伸；
    - s[i+k] < s[j+k]：j..j+k 都不可能成为更优起点，j 跳到 j+k+1；
    - s[i+k] > s[j+k]：同理 i 跳到 i+k+1。
    跳跃保证失败者整体后移，均摊 O(L)。
    """
    s = list(map(ord, s))
    n = len(s)
    i, j, k = 0, 1, 0
    while k < n and i < n and j < n:
        d = s[(i + k) % n] - s[(j + k) % n]
        if d == 0:
            k += 1
        else:
            if d > 0:
                i += k + 1  # i..i+k 全部落败，一起跳过
            else:
                j += k + 1
            if i == j:
                j += 1  # 两指针不能重合
            k = 0
    return ''.join(chr(c) for c in s[min(i, j):] + s[:min(i, j)])

def main() -> None:
    data = sys.stdin.read().split()
    a, b = data[0], data[1]
    ma = min_rotation(a)  # 两串相等当且仅当最小表示相等
    if ma == min_rotation(b):
        print('Yes')
        print(ma)
    else:
        print('No')

main()
