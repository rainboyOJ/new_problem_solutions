#!/usr/bin/env python3
"""生成 P4145 小数据：n 个数 + m 次开根号/求和操作，规模适合暴力对拍。

数值故意混合“很小的值”与“很大的值”，覆盖这些边界：
- 值恰好为 1（或开方一次后变 1）：整段开方不再变化，考验最大值剪枝；
- 大值（1e9 级别）：需要多次开方才收敛到 1，考验摊还递归路径。
"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 100)
    print(n)
    values = []
    for _ in range(n):
        # 约 30% 概率取 1..10 的小值，其余取 1..1e9 的大值。
        if random.random() < 0.3:
            values.append(random.randint(1, 10))
        else:
            values.append(random.randint(1, 10**9))
    print(" ".join(map(str, values)))
    print(m)
    for _ in range(m):
        k = random.randint(0, 1)
        l = random.randint(1, n)
        r = random.randint(1, n)
        # 故意随机生成 l、r，允许出现 l > r，考验程序内交换分支。
        print(k, l, r)


if __name__ == "__main__":
    main()
