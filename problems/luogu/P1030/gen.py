#!/usr/bin/env python3
import os
import random


class Node:
    def __init__(self, value: str):
        self.value = value
        self.left = None
        self.right = None


def build_tree(labels):
    if not labels:
        return None
    root = Node(labels[0])
    for ch in labels[1:]:
        cur = root
        while True:
            if random.randint(0, 1) == 0:
                if cur.left is None:
                    cur.left = Node(ch)
                    break
                cur = cur.left
            else:
                if cur.right is None:
                    cur.right = Node(ch)
                    break
                cur = cur.right
    return root


def inorder(node, out):
    if node is None:
        return
    inorder(node.left, out)
    out.append(node.value)
    inorder(node.right, out)


def postorder(node, out):
    if node is None:
        return
    postorder(node.left, out)
    postorder(node.right, out)
    out.append(node.value)


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(1, 8)
    labels = [chr(ord("A") + i) for i in range(n)]
    random.shuffle(labels)
    root = build_tree(labels)

    in_order = []
    post_order = []
    inorder(root, in_order)
    postorder(root, post_order)

    print("".join(in_order))
    print("".join(post_order))


if __name__ == "__main__":
    main()
