#!/usr/bin/env python3
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp=[1]*n
        for _ in range(1,m):
            for j in range(1,n): dp[j]+=dp[j-1]
        return dp[-1]
def main():
    m,n=map(int,input().split())
    print(Solution().uniquePaths(m,n))
if __name__=="__main__": main()
