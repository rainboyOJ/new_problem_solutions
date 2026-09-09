#!/usr/bin/env python3
"""gen.py：B. Treasure 对拍数据生成器。

生成小网格随机字母，并随机嵌入单词 W 的若干次出现（直线或 L 形），
保证对拍数据经常有非零答案，同时让两边的暴力/正解都能发现它们。

输出格式与官方数据一致：
  第一行：单词 W
  第二行：行数 R
  第三行：列数 C
  之后 R 行，每行 C 个由空格分隔的大写字母
"""
import random
import sys

ALPHABET = "ABCDEFGH"
DIRS = [
    (-1, 0), (-1, 1), (0, 1), (1, 1),  # 上、右上、右、右下
    (1, 0), (1, -1), (0, -1), (-1, -1),  # 下、左下、左、左上
]
PERP = {  # 每个方向的两个垂直方向（编号与上表一致）
    0: [2, 6], 1: [3, 7], 2: [0, 4], 3: [1, 5],
    4: [2, 6], 5: [3, 7], 6: [0, 4], 7: [1, 5],
}


def rand_word(rng, max_len):
    """生成长度 2..max_len、字母互不相同的大写单词。"""
    letters = rng.sample(ALPHABET, k=rng.randint(2, max_len))
    return "".join(letters)


def embed_straight(rng, g, R, C, w):
    """尝试在随机位置沿随机方向放置一次直线出现，成功返回 True。"""
    L = len(w)
    for _ in range(100):
        i = rng.randrange(R)
        j = rng.randrange(C)
        d = rng.randrange(8)
        dx, dy = DIRS[d]
        cells = [(i + dx * t, j + dy * t) for t in range(L)]
        if all(0 <= x < R and 0 <= y < C for x, y in cells):
            for t, (x, y) in enumerate(cells):
                g[x][y] = w[t]
            return True
    return False


def embed_lshape(rng, g, R, C, w):
    """尝试在随机位置沿随机方向放置一次 L 形出现，成功返回 True。"""
    L = len(w)
    if L < 3:  # L 形要求第一段至少 2 个字母，所以单词长度至少 3
        return False
    for _ in range(200):
        i = rng.randrange(R)
        j = rng.randrange(C)
        d1 = rng.randrange(8)
        dx1, dy1 = DIRS[d1]
        k = rng.randint(2, L - 1)  # 第一段 k 个字母，第二段 L-k 个字母
        d2 = rng.choice(PERP[d1])
        dx2, dy2 = DIRS[d2]
        cells = [(i + dx1 * t, j + dy1 * t) for t in range(k)]
        cells += [(i + dx1 * (k - 1) + dx2 * t, j + dy1 * (k - 1) + dy2 * t)
                  for t in range(1, L - k + 1)]
        if all(0 <= x < R and 0 <= y < C for x, y in cells):
            for t, (x, y) in enumerate(cells):
                g[x][y] = w[t]
            return True
    return False


def gen(rng):
    R = rng.randint(2, 12)
    C = rng.randint(2, 12)
    w = rand_word(rng, min(8, R + C))

    # 随机填充网格（小字母表让单词更可能自然出现）
    g = [[rng.choice(ALPHABET) for _ in range(C)] for _ in range(R)]

    # 随机嵌入 0~3 次出现，保证常有非零答案
    for _ in range(rng.randint(0, 3)):
        if rng.random() < 0.5:
            embed_straight(rng, g, R, C, w)
        else:
            embed_lshape(rng, g, R, C, w)

    out = [w, str(R), str(C)]
    out += [" ".join(row) for row in g]
    return "\n".join(out)


if __name__ == "__main__":
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else random.randrange(10**9)
    rng = random.Random(seed)
    print(gen(rng))
