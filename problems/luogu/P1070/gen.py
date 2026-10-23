#!/usr/bin/env python3
"""gen.py：P1070 道路游戏 随机数据生成器。

环境变量：
  DUPAI_SEED  随机种子（duipai.py 会注入）
用法：
  python3 gen.py > case.in

默认生成小数据（n, m <= 8），便于和 brute.cpp 对拍。
"""
import os
import random
import sys


def main():
    seed = int(os.environ.get("DUPAI_SEED", "0"))
    random.seed(seed)

    # 小数据规模，覆盖 n=2 环形回绕、k=p 边界、负收益等情形
    n = random.randint(2, 8)
    m = random.randint(1, 8)
    p = random.randint(1, m)

    lines = [f"{n} {m} {p}"]
    for _ in range(n):
        row = [str(random.randint(1, 100)) for _ in range(m)]
        lines.append(" ".join(row))
    # 购买花费：1~100，覆盖「花费大于收益导致负收益」的边界
    cost = [str(random.randint(1, 100)) for _ in range(n)]
    lines.append(" ".join(cost))

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
