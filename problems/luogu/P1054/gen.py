#!/usr/bin/env python3
import random


def add_spaces(expr: str) -> str:
    out = []
    for ch in expr:
        if ch in "+-*^()":
            if random.randint(0, 1) == 0:
                out.append(" ")
            out.append(ch)
            if random.randint(0, 1) == 0:
                out.append(" ")
        else:
            out.append(ch)
    if random.randint(0, 1) == 0:
        out.insert(0, " " * random.randint(0, 2))
    if random.randint(0, 1) == 0:
        out.append(" " * random.randint(0, 2))
    return "".join(out)


def gen_atom(depth: int) -> str:
    if depth <= 0 or random.random() < 0.45:
        if random.randint(0, 1) == 0:
            return "a"
        return str(random.randint(1, 3))
    return "(" + gen_expr(depth - 1) + ")"


def gen_exp_const() -> str:
    return str(random.randint(1, 2))


def gen_power(depth: int) -> str:
    expr = gen_atom(depth)
    while depth > 0 and random.random() < 0.2:
        expr += "^" + gen_exp_const()
        break
    return expr


def gen_term(depth: int) -> str:
    expr = gen_power(depth)
    while depth > 0 and random.random() < 0.35:
        expr += "*" + gen_power(depth - 1)
    return expr


def gen_expr(depth: int) -> str:
    expr = gen_term(depth)
    while depth > 0 and random.random() < 0.4:
        expr += random.choice(["+", "-"]) + gen_term(depth - 1)
    return expr


def equivalent_expr(expr: str) -> str:
    candidates = [
        "((" + expr + "))",
        "(" + expr + ")+(a-a)",
        "(" + expr + ")-(a-a)",
        "(" + expr + ")*(1^1)",
        "(" + expr + ")^1",
        "(" + expr + ")+((1-1)*a)",
    ]
    random.shuffle(candidates)
    for s in candidates:
        if len(s) <= 50:
            return s
    return expr


def invalid_expr(expr: str) -> str:
    candidates = [
        "(" + expr,
        expr + ")",
        expr + "+",
        "(" + expr + "))*",
    ]
    random.shuffle(candidates)
    return candidates[0]


def random_expr(limit_len: int = 50) -> str:
    while True:
        s = gen_expr(2)
        if len(s) <= limit_len:
            return s


def main():
    random.seed()
    base = random_expr(28)
    n = random.randint(2, 6)

    options = [equivalent_expr(base)]
    while len(options) < n:
        kind = random.random()
        if kind < 0.4:
            s = equivalent_expr(base)
        elif kind < 0.75:
            s = random_expr(40)
        else:
            s = invalid_expr(random_expr(20))
        if len(s) <= 50:
            options.append(s)

    print(add_spaces(base))
    print(n)
    for s in options:
        print(add_spaces(s))


if __name__ == "__main__":
    main()
