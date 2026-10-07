#!/usr/bin/env python3
"""A. Number 随机数据生成器（对拍用）。

生成 k <= 12 的小数据：多组数据，先给 k 再给 k 位数字字符串。
约 30% 概率生成"进位链"数据（某一位为 9，更低位在 5~9 之间），
用来覆盖连锁进位和最高位变长的边界情况。
"""
import random

random.seed()


def gen_one():
    # 进位链数据：从右数第 cut 位为 9，其右侧（更低位）都是 5~9，
    # 处理到该位时必然产生连锁进位（可能把数变长）。
    if random.random() < 0.3:
        k = random.randint(2, 12)
        cut = random.randint(1, k - 1)  # 从右数第 cut 位，1 起
        digs = []
        for i in range(k):  # 从左到右构造
            pos_from_right = k - 1 - i
            if pos_from_right < cut:
                digs.append(random.randint(5, 9))
            elif pos_from_right == cut:
                digs.append(9)
            else:
                digs.append(random.randint(0, 9) if i > 0 else random.randint(1, 9))
        return k, "".join(map(str, digs))

    k = random.randint(1, 12)
    if k == 1:
        return 1, str(random.randint(0, 9))
    digs = [random.randint(1, 9)] + [random.randint(0, 9) for _ in range(k - 1)]
    return k, "".join(map(str, digs))


def main():
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        k, n = gen_one()
        print(k)
        print(n)


if __name__ == "__main__":
    main()