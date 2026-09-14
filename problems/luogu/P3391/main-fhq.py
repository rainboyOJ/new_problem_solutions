"""洛谷 P3391：隐式 FHQ-Treap 区间翻转。"""

import random
import sys


sys.setrecursionlimit(300000)


class Node:
    """模板节点增加 rev，用于懒标记区间翻转。"""

    __slots__ = ("val", "pri", "size", "left", "right", "rev")

    def __init__(self, val, pri):
        self.val = val
        self.pri = pri
        self.size = 1
        self.left = None
        self.right = None
        self.rev = False


class ImplicitFHQTreap:
    """中序遍历表示序列；split 按元素个数而非数值分裂。"""

    def __init__(self):
        self.root = None
        self.rng = random.Random(233)

    def size(self, u):
        return u.size if u is not None else 0

    def push_up(self, u):
        u.size = self.size(u.left) + self.size(u.right) + 1

    def push_down(self, u):
        if u is None or not u.rev:
            return
        u.left, u.right = u.right, u.left
        if u.left is not None:
            u.left.rev = not u.left.rev
        if u.right is not None:
            u.right.rev = not u.right.rev
        u.rev = False

    def new_node(self, val):
        return Node(val, self.rng.randint(1, 2**31 - 1))

    def split(self, u, k):
        """返回前 k 个元素和其余元素组成的两棵树。"""
        if u is None:
            return None, None

        self.push_down(u)
        if self.size(u.left) >= k:
            x, u.left = self.split(u.left, k)
            self.push_up(u)
            return x, u

        u.right, y = self.split(u.right, k - self.size(u.left) - 1)
        self.push_up(u)
        return u, y

    def merge(self, x, y):
        """合并两段相邻序列，x 中元素全部在 y 之前。"""
        if x is None or y is None:
            return x if y is None else y

        if x.pri > y.pri:
            self.push_down(x)
            x.right = self.merge(x.right, y)
            self.push_up(x)
            return x

        self.push_down(y)
        y.left = self.merge(x, y.left)
        self.push_up(y)
        return y

    def append(self, val):
        self.root = self.merge(self.root, self.new_node(val))

    def reverse_range(self, left, right):
        first, last = self.split(self.root, right)
        before, middle = self.split(first, left - 1)
        middle.rev = not middle.rev
        self.root = self.merge(self.merge(before, middle), last)

    def inorder(self, u, answer):
        if u is None:
            return
        self.push_down(u)
        self.inorder(u.left, answer)
        answer.append(str(u.val))
        self.inorder(u.right, answer)


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    n, m = data[0], data[1]
    treap = ImplicitFHQTreap()
    for value in range(1, n + 1):
        treap.append(value)

    pos = 2
    for _ in range(m):
        left, right = data[pos], data[pos + 1]
        pos += 2
        treap.reverse_range(left, right)

    answer = []
    treap.inorder(treap.root, answer)
    sys.stdout.write(" ".join(answer) + "\n")


if __name__ == "__main__":
    main()
