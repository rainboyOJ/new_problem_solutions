#!/usr/bin/env python3
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def reverseKGroup(self, head: ListNode, k: int) -> ListNode:
        dummy = ListNode(0)
        dummy.next = head
        prev = dummy
        while True:
            end = prev
            for _ in range(k):
                end = end.next
                if not end:
                    return dummy.next
            start = prev.next
            nxt = end.next
            a, b = start, start.next
            while b is not nxt:
                c = b.next
                b.next = a
                a = b
                b = c
            start.next = nxt
            prev.next = a
            prev = start


def build(arr):
    dummy = cur = ListNode(0)
    for v in arr:
        cur.next = ListNode(v)
        cur = cur.next
    return dummy.next


def main() -> None:
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    head = build(a)
    head = Solution().reverseKGroup(head, k)
    while head:
        print(head.val, end=" ")
        head = head.next


if __name__ == "__main__":
    main()
