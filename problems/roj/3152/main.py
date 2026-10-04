import sys
from functools import lru_cache

def solve(n: int, m: int) -> int:
    """N*M 棋盘用 1*2 骨牌铺满的方案数（轮廊线 DP）。"""
    # 按行转移：f[j][s] = 已填满前 j 行时，第 j+1 行被上方横牌占住的列集合 s 的方案数
    # 初始 f[0][0]=1，答案 f[m][0]（全部行填完且无伸出）。

    @lru_cache(maxsize=None)
    def g(j: int, s: int) -> int:
        # 处理第 j+1 行：进入时该行已被占列为 s，返回本行填完后传给下一行的伸出列集合
        if j == m:
            return 1 if s == 0 else 0
        # dfs(pos, cur)：逐格填第 j+1 行，cur 为本行向下伸出的列集合
        def dfs(pos: int, cur: int) -> int:
            if pos == n:
                return g(j + 1, cur)
            b = 1 << pos
            if s & b:  # 该格已被上方横牌占据，跳过
                return dfs(pos + 1, cur)
            res = dfs(pos + 1, cur | b)  # 竖牌：向下一行伸出
            if pos + 1 < n and not (s & b << 1):
                res += dfs(pos + 2, cur)  # 横牌：占 (pos,pos+1)，不伸出
            return res
        return dfs(0, 0)

    return g(0, 0)

def main() -> None:
    out = []
    for line in sys.stdin:
        parts = line.split()
        if len(parts) < 2:
            continue
        n, m = int(parts[0]), int(parts[1])
        if n == 0 and m == 0:
            break
        out.append(str(solve(n, m)))
    print('\n'.join(out))

main()
