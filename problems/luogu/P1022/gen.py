#!/usr/bin/env python3
import random


VAR = "x"


def var_term():
    c = random.randint(-9, 9)
    while c == 0:
        c = random.randint(-9, 9)
    if c == 1:
        return VAR
    if c == -1:
        return "-" + VAR
    return f"{c}{VAR}"


def const_term():
    return str(random.randint(-9, 9))


def side_expr():
    parts = []
    m = random.randint(1, 4)
    for _ in range(m):
        if random.randint(0, 1) == 0:
            parts.append(var_term())
        else:
            parts.append(const_term())
    expr = parts[0]
    for item in parts[1:]:
        if item[0] == "-":
            expr += item
        else:
            expr += "+" + item
    return expr


def main():
    random.seed()
    print(f"{side_expr()}={side_expr()}")


if __name__ == "__main__":
    main()
