#!/usr/bin/env python3
"""生成 P4116 小数据：随机树 n<=30，m 次黑白切换与根路径第一个黑点查询，规模适合暴力对拍。

树的形状在随机树 / 链 / 菊花 / 完全二叉树之间轮换，并会生成 n=1 的退化情况，
用来覆盖「根是唯一节点」「路径上无黑点」等边界。
"""
import random

random.seed()


def main():
    shape = random.choice(["random", "chain", "star", "binary"])
    if random.random() < 0.15:
        n = 1  # 退化情况：只有一个节点，没有任何边
    else:
        n = random.randint(2, 30)
    m = random.randint(1, 40)
    print(n, m)
    for i in range(2, n + 1):
        if shape == "chain":
            p = i - 1
        elif shape == "star":
            p = 1
        elif shape == "binary":
            p = i // 2
        else:
            p = random.randint(1, i - 1)
        print(p, i)
    for _ in range(m):
        op = random.randint(0, 1)
        x = random.randint(1, n)
        print(op, x)


if __name__ == "__main__":
    main()
