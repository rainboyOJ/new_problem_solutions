#!/usr/bin/env python3
import os
import random


class Node:
    def __init__(self, kind, left=None, right=None, var_id=None):
        self.kind = kind
        self.left = left
        self.right = right
        self.var_id = var_id


def build_tree(vars_list):
    if len(vars_list) == 1:
        node = Node("var", var_id=vars_list[0])
        if random.randint(0, 1) == 0:
            node = Node("not", left=node)
        return node

    cut = random.randint(1, len(vars_list) - 1)
    left = build_tree(vars_list[:cut])
    right = build_tree(vars_list[cut:])
    node = Node(random.choice(["and", "or"]), left=left, right=right)
    if random.randint(0, 3) == 0:
        node = Node("not", left=node)
    return node


def to_postfix(node, out):
    if node.kind == "var":
        out.append(f"x{node.var_id}")
    elif node.kind == "not":
        to_postfix(node.left, out)
        out.append("!")
    else:
        to_postfix(node.left, out)
        to_postfix(node.right, out)
        out.append("&" if node.kind == "and" else "|")


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(2, 8)
    q = random.randint(1, 10)
    vars_list = list(range(1, n + 1))
    root = build_tree(vars_list)

    postfix = []
    to_postfix(root, postfix)
    print(" ".join(postfix))
    print(n)
    print(*[random.randint(0, 1) for _ in range(n)])
    print(q)
    for _ in range(q):
        print(random.randint(1, n))


if __name__ == "__main__":
    main()
