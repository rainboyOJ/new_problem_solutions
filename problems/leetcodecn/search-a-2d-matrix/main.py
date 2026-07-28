#!/usr/bin/env python3
from typing import List
class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m,n=len(matrix),len(matrix[0]); l,r=0,m*n-1
        while l<=r:
            mid=(l+r)//2; v=matrix[mid//n][mid%n]
            if v==target: return True
            if v<target: l=mid+1
            else: r=mid-1
        return False
def main():
    m,n,t=map(int,input().split())
    g=[list(map(int,input().split())) for _ in range(m)]
    print(Solution().searchMatrix(g,t))
if __name__=="__main__": main()
