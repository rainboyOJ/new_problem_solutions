#!/usr/bin/env python3
# gen.py：小数据随机数据生成器，用于对拍。
# 随机生成 (音符, 次数) 段：次数以小值为主（1..9），
# 也会混合生成多位数字次数（如 d10、b125），并保证展开后的总长度可控。

import random
import sys


def gen_one(seed):
    rnd = random.Random(seed)

    # 段数 1..25（压缩串最短为 "x1"，长度为 2）
    k = rnd.randint(1, 25)

    pairs = []
    total = 0
    MAX_LEN = 20000  # 限制总展开长度，保证暴力展开不超内存
    for _ in range(k):
        ch = chr(rnd.randint(ord('a'), ord('z')))
        # 大部分情况小次数，约 1/3 概率生成多位数字次数
        if rnd.random() < 0.35:
            cnt = rnd.randint(10, 999)
        else:
            cnt = rnd.randint(1, 9)
        # 超出剩余预算时截断到剩余预算
        if total + cnt > MAX_LEN:
            cnt = max(1, MAX_LEN - total)
        total += cnt
        pairs.append((ch, cnt))
        if total >= MAX_LEN:
            break

    s = ''.join(ch + str(cnt) for ch, cnt in pairs)

    # c 随机：小值、接近周期倍数、大随机值都覆盖
    choice = rnd.random()
    if choice < 0.3:
        c = rnd.randint(0, 100)
    elif choice < 0.6:
        c = total * rnd.randint(0, 5) + rnd.randint(0, max(1, total - 1))
    else:
        c = rnd.randint(0, 10**12)

    return s, c


def main():
    seed = sys.argv[1] if len(sys.argv) > 1 else "0"
    s, c = gen_one(seed)
    print(s)
    print(c)


if __name__ == '__main__':
    main()