#!/usr/bin/env python3
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if not headA or not headB:
            return None
        a, b = headA, headB
        while a is not b:
            a = a.next if a else headB
            b = b.next if b else headA
        return a


def build(arr):
    dummy = cur = ListNode(0)
    for v in arr:
        cur.next = ListNode(v)
        cur = cur.next
    return dummy.next


def main() -> None:
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    ha, hb = build(a), build(b)
    ans = Solution().getIntersectionNode(ha, hb)
    print(ans.val if ans else -1)


if __name__ == "__main__":
    main()
