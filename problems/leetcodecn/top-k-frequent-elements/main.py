#!/usr/bin/env python3
from typing import List
from collections import Counter
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        return [x for x,_ in Counter(nums).most_common(k)]
def main():
    n,k=map(int,input().split()); a=list(map(int,input().split()))
    print(*Solution().topKFrequent(a,k))
if __name__=="__main__": main()
