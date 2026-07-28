#!/usr/bin/env python3
class Node:
    def __init__(self, x):
        self.val = x
        self.next = None
        self.random = None


class Solution:
    def copyRandomList(self, head: Node) -> Node:
        if not head:
            return None
        m = {}
        p = head
        while p:
            m[p] = Node(p.val)
            p = p.next
        p = head
        while p:
            m[p].next = m.get(p.next)
            m[p].random = m.get(p.random)
            p = p.next
        return m[head]


def build(arr):
    if not arr:
        return None
    nodes = [Node(v) for v in arr]
    for i in range(len(nodes) - 1):
        nodes[i].next = nodes[i + 1]
    return nodes[0]


def main() -> None:
    n = int(input())
    a = list(map(int, input().split()))
    head = build(a)
    copied = Solution().copyRandomList(head)
    while copied:
        print(copied.val, end=" ")
        copied = copied.next


if __name__ == "__main__":
    main()
