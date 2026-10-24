#!/usr/bin/env python3
"""gen.py：为 luogu/P3205 生成对拍数据。

按模式覆盖四类小数据，保证 main.cpp 与 brute.cpp 的比较落在二者共同适用范围：

- random：随机身高序列，绝大多数不可达（期望输出 0）。
- reachable：随机初始顺序按题面规则模拟得到的目标队形，答案一定非零。
- inc：严格递增，答案应为 2^(n-1)。
- dec：严格递减，答案应为 0（n = 1 时为 1）。

环境变量 DUPAI_SEED 存在时作为随机种子，便于复现。
"""
import os
import random


def simulate(initial):
    """按题面规则把初始顺序排成最终队形。"""
    cur = []
    for k, x in enumerate(initial):
        if k == 0:
            cur.append(x)
        elif x > initial[k - 1]:
            cur.append(x)
        else:
            cur.insert(0, x)
    return cur


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(1, 9)
    pool = range(1000, 2000)

    mode = random.choice(["random", "random", "reachable", "reachable", "inc", "dec"])

    if mode == "inc":
        arr = sorted(random.sample(pool, n))
    elif mode == "dec":
        arr = sorted(random.sample(pool, n), reverse=True)
    elif mode == "reachable":
        initial = random.sample(pool, n)
        arr = simulate(initial)
    else:
        arr = random.sample(pool, n)

    print(n)
    print(*arr)


if __name__ == "__main__":
    main()
