#!/usr/bin/env python3
import os
import random


LIMIT = 2**31 - 1
OPS = ["+", "-", "*", "/", "^"]


class Node:
    def __init__(self, kind, value=0, op="", left=None, right=None):
        self.kind = kind
        self.value = value
        self.op = op
        self.left = left
        self.right = right


def quick_pow(a, b):
    ans = 1
    while b > 0:
        if b & 1:
            ans *= a
        a *= a
        b >>= 1
        if abs(ans) > LIMIT or abs(a) > LIMIT:
            raise ValueError("overflow")
    return ans


def eval_node(node):
    if node.kind == "num":
        return node.value

    left_value = eval_node(node.left)
    right_value = eval_node(node.right)

    if node.op == "+":
        value = left_value + right_value
    elif node.op == "-":
        value = left_value - right_value
    elif node.op == "*":
        value = left_value * right_value
    elif node.op == "/":
        if right_value == 0:
            raise ValueError("divide by zero")
        value = int(left_value / right_value)
    else:
        if right_value < 0 or right_value > 9:
            raise ValueError("bad exponent")
        value = quick_pow(left_value, right_value)

    if abs(value) > LIMIT:
        raise ValueError("overflow")
    return value


def render(node):
    if node.kind == "num":
        return str(node.value)
    return "(" + render(node.left) + node.op + render(node.right) + ")"


def build_expr(depth):
    if depth >= 4 or random.random() < 0.35:
        return Node("num", value=random.randint(0, 9))

    for _ in range(120):
        op = random.choice(OPS)
        left = build_expr(depth + 1)
        right = build_expr(depth + 1)
        node = Node("op", op=op, left=left, right=right)
        try:
            eval_node(node)
        except ValueError:
            continue

        if len(render(node)) <= 96:
            return node

    return Node("num", value=random.randint(0, 9))


def build_root():
    for _ in range(200):
        root = build_expr(0)
        text = render(root)
        if root.kind == "op" and len(text) <= 96:
            return root
    return Node("op", op="+", left=Node("num", value=1), right=Node("num", value=2))


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is not None:
        random.seed(int(seed_text))
    else:
        random.seed()

    root = build_root()
    text = render(root)
    if text.startswith("(") and text.endswith(")"):
        text = text[1:-1]
    print(text)


if __name__ == "__main__":
    main()
