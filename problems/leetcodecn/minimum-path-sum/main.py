#!/usr/bin/env python3
from typing import List
class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        m,n=len(grid),len(grid[0])
        dp=grid[0][:]
        for j in range(1,n): dp[j]+=dp[j-1]
        for i in range(1,m):
            dp[0]+=grid[i][0]
            for j in range(1,n): dp[j]=grid[i][j]+min(dp[j],dp[j-1])
        return dp[-1]
def main():
    m,n=map(int,input().split())
    g=[list(map(int,input().split())) for _ in range(m)]
    print(Solution().minPathSum(g))
if __name__=="__main__": main()
