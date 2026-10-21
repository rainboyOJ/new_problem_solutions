#!/usr/bin/env python3
# 随机生成小数据：n 个小朋友、k 条要求，五种类型都会出现。
# 一半数据完全随机（容易产生矛盾），一半先取一组"真解"再反推要求（保证有解）。
import random


def main():
    random.seed()
    n = random.randint(1, 5)
    k = random.randint(1, 6)

    lines = []
    if random.random() < 0.5:
        # 完全随机：可能出现自环型矛盾，也可能出现严格关系成环
        for _ in range(k):
            kind = random.randint(1, 5)
            a = random.randint(1, n)
            b = random.randint(1, n)
            lines.append(f"{kind} {a} {b}")
    else:
        # 先取一组真解，再逐条反推与它相容的要求
        x = [0] + [random.randint(1, n) for _ in range(n)]
        for _ in range(k):
            kind = random.randint(1, 5)
            a = random.randint(1, n)
            b = random.randint(1, n)

            if kind == 1:
                # 要求相等：把 x[b] 改成 x[a]，真解仍然成立
                x[b] = x[a]
                lines.append(f"1 {a} {b}")
            elif kind == 2:
                # 要求 x_a < x_b；真解不满足时换成反向的 3，仍然相容
                if x[a] < x[b]:
                    lines.append(f"2 {a} {b}")
                else:
                    lines.append(f"3 {a} {b}")
            elif kind == 3:
                # 要求 x_a >= x_b
                if x[a] >= x[b]:
                    lines.append(f"3 {a} {b}")
                else:
                    lines.append(f"5 {a} {b}")
            elif kind == 4:
                # 要求 x_a > x_b
                if x[a] > x[b]:
                    lines.append(f"4 {a} {b}")
                else:
                    lines.append(f"5 {a} {b}")
            else:
                # 要求 x_a <= x_b
                if x[a] <= x[b]:
                    lines.append(f"5 {a} {b}")
                else:
                    lines.append(f"3 {a} {b}")

    print(n, k)
    print("\n".join(lines))


if __name__ == "__main__":
    main()
