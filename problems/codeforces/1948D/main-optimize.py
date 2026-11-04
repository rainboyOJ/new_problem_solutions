"""
题意: 问号可以替换成任意小写字母, 求最长的 Tandem Repeats (前半 == 后半) 的长度.

这是 main.py 的优化版 (原版 O(n^2) 的 Python 双层循环在 n=5000 时约 3~5s, 会 TLE).

沿用 main.py 里的数学结论:
    对固定的半长 q, 令
        b[i] = 1  if  s[i] 与 s[i+q] 相容 (相等, 或有一边是 '?')
        b[i] = 0  otherwise
    则 [st, st+2q) 是 Tandem Repeats  <=>  b[st .. st+q-1] 全是 1
    即: b 中必须存在一段长度 >= q 的连续 1.

    (对应 main.py 里的 f 递推: f[i] = f[i-1] + 1 if b[i] else 0,
     当 f[i] == q 时就找到了一个答案.
     注意是拿 b[i] 判断, 不是拿 a[i] 和 a[i-q] 比较 —— +q 的比较已经在 b 里做完了.)

优化点: 把两处 Python 级循环换成大整数位运算
    1. 每种字符出现的位置压成 bitmask, 则
           b = (?mask | (?mask >> q)) | Σ (letter_mask & (letter_mask >> q))
       一次位运算算出整排 b, 而不是 n 次字符比较.
    2. "是否存在长度 q 的连续 1" 用倍增法 m &= m >> L (L = 1,2,4,...),
       约 log q 次大整数移位, 而不是 q 次扫描.
    3. q 从大到小枚举, 找到即退出, 并加 2q <= ans 剪枝.

复杂度: 约 O(n^2 / wordsize * log n), 实际几乎全在 C 层.
"""

import sys


def has_run(m, q):
    """m 的第 i 位为 1 表示 b[i]==1; 判断是否存在长度 >= q 的连续 1."""
    L = 1
    while L * 2 <= q:
        m &= m >> L          # 现在第 i 位为 1  <=>  原 m[i-L+1 .. i] 全 1 (长度 2L)
        L *= 2
        if not m:
            return False
    r = q - L                # 还差 r 位, 再对齐一次
    if r:
        m &= m >> r
    return m != 0


def check_bits(n, qmask, letters, q):
    """判断半长 q 下是否存在 Tandem Repeats."""
    # 相容位置: 两边都是 '?' , 或者某一边是 '?' , 或者同字母
    m = qmask | (qmask >> q)
    for a in letters:
        m |= a & (a >> q)
    m &= (1 << (n - q)) - 1     # 只保留 0 .. n-q-1
    return bool(m) and has_run(m, q)


def solve(data):
    out = []
    for s in data:
        n = len(s)
        if n < 2:                       # 长度 <2 不可能有 tandem repeat
            out.append('0')
            continue

        # 每种字符出现在哪些位置: bit i 为 1 <=> s[i] == ch
        pos = {}
        for i, ch in enumerate(s):
            pos[ch] = pos.get(ch, 0) | (1 << i)
        qmask = pos.pop('?', 0)         # '?' 的位置
        letters = list(pos.values())

        ans = 0
        for q in range(n // 2, 0, -1):  # 从大到小枚举, 找到就能提前退出
            if 2 * q <= ans:
                break
            if check_bits(n, qmask, letters, q):
                ans = 2 * q
                break
        out.append(str(ans))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    _t, *data = sys.stdin.buffer.read().decode().split()
    solve(data)
