#!/usr/bin/env python3
import heapq
from typing import List
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        pq=[]
        for x in nums:
            heapq.heappush(pq,x)
            if len(pq)>k: heapq.heappop(pq)
        return pq[0]
def main():
    n,k=map(int,input().split()); a=list(map(int,input().split()))
    print(Solution().findKthLargest(a,k))
if __name__=="__main__": main()
