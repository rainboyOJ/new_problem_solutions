#!/usr/bin/env python3
"""P9727 (Aqre) 的 special judge。

题面允许多解（“If there are multiple solution, output any”），所以不能用
文本 diff 对拍。本 checker 做三件事：

1. 校验输出格式（第一行是 1 的个数，后面 n 行每行 m 个 0/1）；
2. 校验矩阵本身合法（没有 4 个连续同号；1 四连通；矩阵里 1 的个数与第一行一致）；
3. 与参考个数（由 brute 或正解应得的答案）比较，确认第一行报的是最大值。

用法：python3 checker.py <输入文件> <选手输出文件> [<参考答案文件>]
缺少参考答案时只做 1、2 两项（用于单独自检 main 的构造是否合法）。
退出码 0 表示通过。"""
import sys


def parse_input(path):
    with open(path, encoding="utf-8") as f:
        tokens = f.read().split()
    pos = 0
    t = int(tokens[pos]); pos += 1
    cases = []
    for _ in range(t):
        n = int(tokens[pos]); m = int(tokens[pos + 1]); pos += 2
        cases.append((n, m))
    return cases


def check_case(n, m, ones, mat):
    """返回错误信息，None 表示合法。"""
    if len(mat) != n:
        return f"矩阵行数 {len(mat)} != {n}"
    for i, row in enumerate(mat):
        if len(row) != m:
            return f"第 {i} 行长度 {len(row)} != {m}"
        if any(c not in "01" for c in row):
            return f"第 {i} 行含非 0/1 字符"
    g = [[int(c) for c in row] for row in mat]

    for i in range(n):
        for j in range(m - 3):
            s = g[i][j] + g[i][j + 1] + g[i][j + 2] + g[i][j + 3]
            if s in (0, 4):
                return f"第 {i} 行第 {j}..{j + 3} 列是 4 个连续的 {s // 4}"
    for j in range(m):
        for i in range(n - 3):
            s = g[i][j] + g[i + 1][j] + g[i + 2][j] + g[i + 3][j]
            if s in (0, 4):
                return f"第 {j} 列第 {i}..{i + 3} 行是 4 个连续的 {s // 4}"

    cells = [(i, j) for i in range(n) for j in range(m) if g[i][j]]
    if not cells:
        return "矩阵中没有 1，无法连通"
    if len(cells) != ones:
        return f"第一行报 {ones} 个 1，矩阵里实际有 {len(cells)} 个"

    seen = {cells[0]}
    stack = [cells[0]]
    while stack:
        x, y = stack.pop()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            a, b = x + dx, y + dy
            if 0 <= a < n and 0 <= b < m and g[a][b] and (a, b) not in seen:
                seen.add((a, b))
                stack.append((a, b))
    if len(seen) != len(cells):
        return f"1 不连通（可达 {len(seen)} / 共 {len(cells)}）"
    return None


def main():
    if len(sys.argv) < 3:
        print("用法: python3 checker.py <输入文件> <选手输出文件> [<参考答案文件>]")
        return 2
    cases = parse_input(sys.argv[1])

    with open(sys.argv[2], encoding="utf-8") as f:
        tokens = f.read().split()

    expected = None
    if len(sys.argv) >= 4:
        with open(sys.argv[3], encoding="utf-8") as f:
            expected = [int(x) for x in f.read().split()]

    pos = 0
    ok = True
    for idx, (n, m) in enumerate(cases):
        if pos >= len(tokens):
            print(f"case {idx} ({n}x{m}): 输出提前结束")
            return 1
        ones = int(tokens[pos]); pos += 1
        mat = tokens[pos:pos + n]; pos += n
        err = check_case(n, m, ones, mat)
        if err:
            print(f"case {idx} ({n}x{m}): {err}")
            ok = False
            continue
        if expected is not None:
            if idx >= len(expected):
                print(f"case {idx} ({n}x{m}): 参考答案不足")
                return 1
            if ones != expected[idx]:
                print(f"case {idx} ({n}x{m}): 报 {ones} 个 1，最优值是 {expected[idx]}")
                ok = False
    if pos != len(tokens):
        print("输出末尾有多余内容")
        ok = False

    if ok:
        print(f"SPJ OK: {len(cases)} 个 case 全部合法"
              + ("，且 1 的个数均为最优" if expected is not None else ""))
        return 0
    return 1


if __name__ == "__main__":
    sys.exit(main())
