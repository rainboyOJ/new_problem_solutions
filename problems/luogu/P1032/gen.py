#!/usr/bin/env python3
"""P1032 字串变换：随机小数据生成器。

生成很小的起始串/目标串与 1~3 条替换规则，供对拍使用：
- 字母表只有 a、b，串长不超过 5，规则两端长度不超过 2；
- 这样十步内所有可达串长度不超过 15，状态数有界（约 2^16），
  brute.cpp 的递归枚举和 main.cpp 的 BFS 都能快速跑完。
注意：本题是"疑似错题"，某些极端规则组合（单字符替换成很长的串）
会让十步内的状态数爆炸，对拍小数据刻意避开这种情况。
"""

import random
import sys


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
    random.seed(seed)

    alphabet = "ab"
    a = "".join(random.choice(alphabet) for _ in range(random.randint(1, 5)))
    b = "".join(random.choice(alphabet) for _ in range(random.randint(1, 5)))
    if random.random() < 0.2:
        b = a  # 偶尔让起始串等于目标串，覆盖答案 0 的用例

    lines = ["%s %s" % (a, b)]
    for _ in range(random.randint(1, 3)):
        f = "".join(random.choice(alphabet) for _ in range(random.randint(1, 2)))
        t = "".join(random.choice(alphabet) for _ in range(random.randint(1, 2)))
        lines.append("%s %s" % (f, t))
    print("\n".join(lines))


if __name__ == "__main__":
    main()
