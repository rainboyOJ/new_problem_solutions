#!/usr/bin/env python3
import random


VARS = list("abcdef")


def rand_bound():
    if random.randint(0, 4) == 0:
        return "n"
    return str(random.randint(1, 6))


def rand_target():
    typ = random.randint(0, 3)
    if typ == 0:
        return "O(1)"
    if typ == 1:
        return "O(n)"
    return f"O(n^{random.randint(1, 4)})"


def build_case():
    lines = []
    open_stack = []

    total = random.randint(1, 12)
    for _ in range(total):
        can_open = len(lines) < 12
        can_close = len(open_stack) > 0

        if not can_close or (can_open and random.randint(0, 1) == 0):
            var = random.choice(VARS)
            x = rand_bound()
            y = rand_bound()
            lines.append(f"F {var} {x} {y}")
            open_stack.append(var)
        else:
            lines.append("E")
            open_stack.pop()

    # 随机制造一些不平衡情况，方便测 ERR。
    if open_stack and random.randint(0, 2) == 0:
        pass
    else:
        while open_stack and random.randint(0, 1) == 0 and len(lines) < 14:
            lines.append("E")
            open_stack.pop()

    return lines


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        lines = build_case()
        print(len(lines), rand_target())
        for line in lines:
            print(line)


if __name__ == "__main__":
    main()
