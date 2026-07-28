#!/usr/bin/env python3
import heapq
from typing import List, Optional


class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        pq = []
        for i, h in enumerate(lists):
            if h:
                heapq.heappush(pq, (h.val, i, h))
        dummy = cur = ListNode(0)
        while pq:
            _, i, node = heapq.heappop(pq)
            cur.next = node
            cur = cur.next
            if node.next:
                heapq.heappush(pq, (node.next.val, i, node.next))
        return dummy.next


def build(arr):
    dummy = cur = ListNode(0)
    for v in arr:
        cur.next = ListNode(v)
        cur = cur.next
    return dummy.next


def main() -> None:
    k = int(input())
    lists = []
    for _ in range(k):
        n = int(input())
        a = list(map(int, input().split()))
        lists.append(build(a))
    head = Solution().mergeKLists(lists)
    while head:
        print(head.val, end=" ")
        head = head.next


if __name__ == "__main__":
    main()
