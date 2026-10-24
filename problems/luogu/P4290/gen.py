#!/usr/bin/env python3
"""P4290 [HAOI2008] 玩具取名 的随机数据生成器。

输入格式：
  第一行 W I N G 四个整数（每类规则条数）
  随后依 W、I、N、G 顺序列出规则（每行两个字母）
  最后一行是名字字符串

用法：
  python3 gen.py                 # 默认小数据，适合和 brute 对拍
  python3 gen.py --max-len 200 --max-rules 16   # 大数据，测性能
"""
import argparse
import random

ALPHABET = "WING"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--max-len", type=int, default=8, help="名字最大长度（对拍时可小）")
    parser.add_argument("--max-rules", type=int, default=3, help="每类规则最大条数")
    parser.add_argument("--seed", type=int, default=None)
    args = parser.parse_args()

    if args.seed is not None:
        random.seed(args.seed)

    # 每类规则的条数，可能为 0，用来覆盖“没有规则”的边界
    counts = [random.randint(0, args.max_rules) for _ in range(4)]

    lines = [" ".join(str(c) for c in counts)]
    rules = []
    for c in range(4):
        for _ in range(counts[c]):
            x = random.choice(ALPHABET)
            y = random.choice(ALPHABET)
            rules.append(x + y)
            lines.append(x + y)

    # 名字：一半概率随机生成，一半概率由规则“展开”出来，保证有较大概率有解
    max_len = max(1, args.max_len)
    if rules and random.random() < 0.5:
        cur = random.choice(ALPHABET)
        target = random.randint(1, max_len)
        while len(cur) < target:
            pos = random.randrange(len(cur))
            if not rules:
                break
            piece = random.choice(rules)
            cur = cur[:pos] + piece + cur[pos + 1:]
            if len(cur) > max_len:
                break
        name = cur
    else:
        length = random.randint(1, max_len)
        name = "".join(random.choice(ALPHABET) for _ in range(length))

    lines.append(name)
    print("\n".join(lines))


if __name__ == "__main__":
    main()
