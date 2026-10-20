#!/usr/bin/env python3
# 随机生成小数据：n 个农场、m 条信息，三种类型都覆盖。
# 一半数据随机给（容易产生矛盾），一半先取一组"真解"再反推条件（保证可行）。
import random


def main():
    random.seed()
    n = random.randint(1, 5)
    m = random.randint(1, 7)
    lines = []

    if random.random() < 0.5:
        # 随机信息：可能自相矛盾
        for _ in range(m):
            kind = random.randint(1, 3)
            a = random.randint(1, n)
            b = random.randint(1, n)
            if kind == 3:
                lines.append(f"3 {a} {b}")
            else:
                lines.append(f"{kind} {a} {b} {random.randint(1, 5)}")
    else:
        # 先取一组真解 x，再让每条信息与 x 相容
        x = [0] + [random.randint(0, 10) for _ in range(n)]
        for _ in range(m):
            kind = random.randint(1, 3)
            a = random.randint(1, n)
            b = random.randint(1, n)
            if kind == 3:
                x[b] = x[a]  # 强制相等，保证 x 仍是一组真解
                lines.append(f"3 {a} {b}")
            elif kind == 1:
                # x_a - x_b >= c  <=>  c <= x_a - x_b
                diff = x[a] - x[b]
                if diff < 1:
                    lines.append(f"2 {a} {b} {random.randint(1, 5)}")
                else:
                    lines.append(f"1 {a} {b} {random.randint(1, diff)}")
            else:
                # x_a - x_b <= c
                diff = x[a] - x[b]
                lines.append(f"2 {a} {b} {max(0, diff) + random.randint(0, 5)}")

    print(n, m)
    print("\n".join(lines))


if __name__ == "__main__":
    main()
