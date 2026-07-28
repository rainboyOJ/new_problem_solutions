#!/usr/bin/env python3
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        dummy = cur = ListNode(0)
        while l1 and l2:
            if l1.val < l2.val:
                cur.next = l1
                l1 = l1.next
            else:
                cur.next = l2
                l2 = l2.next
            cur = cur.next
        cur.next = l1 or l2
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
    head = Solution().mergeTwoLists(a, b)
    while head:
        print(head.val, end=" ")
        head = head.next


if __name__ == "__main__":
    main()
