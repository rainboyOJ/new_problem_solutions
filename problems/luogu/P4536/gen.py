#!/usr/bin/env python3
import random


def gen_code(depth: int) -> str:
    code = []
    for i in range(depth):
        if i == depth - 1:
            code.append(str(random.randint(1, 4)))
        else:
            code.append(str(random.randint(1, 3)))
    return "T" + "".join(code)


def main():
    random.seed()
    depth = random.randint(1, 7)
    print(gen_code(depth))


if __name__ == "__main__":
    main()
