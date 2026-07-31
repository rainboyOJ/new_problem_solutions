#!/usr/bin/env python3
"""CSP201403C 的随机格式与命令行生成器。"""

import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    letters = random.sample(list("abcdef"), random.randint(1, 6))
    format_parts = []
    for letter in letters:
        format_parts.append(letter)
        if random.choice([False, True]):
            format_parts.append(":")
    print("".join(format_parts))

    line_count = random.randint(1, 5)
    print(line_count)
    for _ in range(line_count):
        tokens = ["tool"]
        for _ in range(random.randint(0, 8)):
            kind = random.randint(0, 3)
            if kind == 0:
                tokens.append("-" + random.choice(letters))
            elif kind == 1:
                tokens.append("-z")
            elif kind == 2:
                tokens.append("value-" + str(random.randint(0, 9)))
            else:
                tokens.append("-" + random.choice("0123456789"))
        print(" ".join(tokens))


if __name__ == "__main__":
    main()
