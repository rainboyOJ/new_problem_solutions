#!/usr/bin/env python3
# gen.py：P9239 的数据生成器。
# 题目输入只有一个大写字母 'A' 或 'B'，两道小问的数据都写死在题面里，
# 所以生成器的唯一职责就是输出一个合法的问号。
# 输入空间只有 {A, B} 两种取值，因此这里偏向“每次随机取一个”，
# 让多次运行能覆盖到两种问法；需要可复现时用 DUPAI_SEED 固定种子。
import os
import random
import sys


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        # 没有外部种子时用随机种子，保证多次运行覆盖 A、B 两种问法。
        random.seed()
    else:
        # 对拍工具会传入 DUPAI_SEED，相同种子得到完全相同的输出。
        random.seed(int(seed_text))

    # 输入只有一个大写字母，表示第几个问题。
    sys.stdout.write(random.choice(["A", "B"]) + "\n")


if __name__ == "__main__":
    main()
