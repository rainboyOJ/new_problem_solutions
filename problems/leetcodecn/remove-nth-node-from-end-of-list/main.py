#!/usr/bin/env python3
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        dummy = ListNode(0)
        dummy.next = head
        fast = slow = dummy
        for _ in range(n):
            fast = fast.next
        while fast.next:
            slow = slow.next
            fast = fast.next
        slow.next = slow.next.next
        return dummy.next


def build(arr):
    dummy = cur = ListNode(0)
    for v in arr:
        cur.next = ListNode(v)
        cur = cur.next
    return dummy.next


def main() -> None:
    length, n = map(int, input().split())
    a = list(map(int, input().split()))
    head = build(a)
    head = Solution().removeNthFromEnd(head, n)
    while head:
        print(head.val, end=" ")
        head = head.next


if __name__ == "__main__":
    main()
