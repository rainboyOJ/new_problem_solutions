#!/usr/bin/env python3
from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        ans, cur = [], []

        def dfs(open, close):
            if open == n and close == n:
                ans.append("".join(cur))
                return
            if open < n:
                cur.append("(")
                dfs(open + 1, close)
                cur.pop()
            if close < open:
                cur.append(")")
                dfs(open, close + 1)
                cur.pop()

        dfs(0, 0)
        return ans


def main():
    n = int(input())
    for s in Solution().generateParenthesis(n):
        print(s)


if __name__ == "__main__":
    main()
