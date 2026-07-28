#!/usr/bin/env python3
from typing import List
class Solution:
    def findMedianSortedArrays(self, a: List[int], b: List[int]) -> float:
        if len(a)>len(b): a,b=b,a
        m,n=len(a),len(b); lo,hi=0,m
        while lo<=hi:
            i=(lo+hi)//2; j=(m+n+1)//2-i
            al=a[i-1] if i>0 else float('-inf')
            ar=a[i] if i<m else float('inf')
            bl=b[j-1] if j>0 else float('-inf')
            br=b[j] if j<n else float('inf')
            if al<=br and bl<=ar:
                return max(al,bl) if (m+n)%2 else (max(al,bl)+min(ar,br))/2
            if al>br: hi=i-1
            else: lo=i+1
        return 0
def main():
    m,n=map(int,input().split()); a=list(map(int,input().split())); b=list(map(int,input().split()))
    print(Solution().findMedianSortedArrays(a,b))
if __name__=="__main__": main()
