#!/usr/bin/env python3
import os
import random


class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


def build_tree(labels):
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


def preorder(node, out):
    if node is None:
        return
    out.append(node.value)
    preorder(node.left, out)
    preorder(node.right, out)


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
    labels = [chr(ord("a") + i) for i in range(n)]
    random.shuffle(labels)
    root = build_tree(labels)

    pre = []
    post = []
    preorder(root, pre)
    postorder(root, post)
    print("".join(pre))
    print("".join(post))


if __name__ == "__main__":
    main()
