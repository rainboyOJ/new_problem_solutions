#!/usr/bin/env python3
from typing import List


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if not digits:
            return []
        mp = ["", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
        ans, cur = [], []

        def dfs(i):
            if i == len(digits):
                ans.append("".join(cur))
                return
            for ch in mp[int(digits[i])]:
                cur.append(ch)
                dfs(i + 1)
                cur.pop()

        dfs(0)
        return ans


def main():
    s = input().strip()
    print(*Solution().letterCombinations(s))


if __name__ == "__main__":
    main()
