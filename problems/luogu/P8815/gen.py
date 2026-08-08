#!/usr/bin/env python3
import os
import random


class Node:
    def __init__(self, op=None, left=None, right=None, value=None):
        self.op = op
        self.left = left
        self.right = right
        self.value = value


def build_expr(leaf_cnt):
    if leaf_cnt == 1:
        return Node(value=random.choice("01"))

    left_cnt = random.randint(1, leaf_cnt - 1)
    right_cnt = leaf_cnt - left_cnt
    op = random.choice("&|")
    return Node(op=op, left=build_expr(left_cnt), right=build_expr(right_cnt))


def precedence(node):
    if node.value is not None:
        return 3
    if node.op == "&":
        return 2
    return 1


def to_string(node, is_right_child=False, parent_prec=0):
    if node.value is not None:
        return node.value

    cur_prec = precedence(node)
    left_text = to_string(node.left, False, cur_prec)
    right_text = to_string(node.right, True, cur_prec)
    expr = left_text + node.op + right_text

    need_paren = cur_prec < parent_prec or (
        is_right_child and cur_prec == parent_prec
    )
    if need_paren:
        return "(" + expr + ")"
    return expr


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    leaf_cnt = random.randint(1, 12)
    root = build_expr(leaf_cnt)
    print(to_string(root))


if __name__ == "__main__":
    main()
