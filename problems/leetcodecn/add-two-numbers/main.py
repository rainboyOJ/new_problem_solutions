#!/usr/bin/env python3
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        dummy = cur = ListNode(0)
        carry = 0
        while l1 or l2 or carry:
            s = (l1.val if l1 else 0) + (l2.val if l2 else 0) + carry
            cur.next = ListNode(s % 10)
            carry = s // 10
            cur = cur.next
            if l1:
                l1 = l1.next
            if l2:
                l2 = l2.next
        return dummy.next


def build(arr):
    dummy = cur = ListNode(0)
    for v in arr:
        cur.next = ListNode(v)
        cur = cur.next
    return dummy.next


def main() -> None:
    n, m = map(int, input().split())
    a = build(list(map(int, input().split())))
    b = build(list(map(int, input().split())))
    head = Solution().addTwoNumbers(a, b)
    while head:
        print(head.val, end=" ")
        head = head.next


if __name__ == "__main__":
    main()
