#!/usr/bin/env python3
from typing import List


class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        n, m = len(s), len(p)
        if n < m:
            return []
        cnt = [0] * 26
        for ch in p:
            cnt[ord(ch) - 97] += 1
        ans = []
        for i in range(n):
            cnt[ord(s[i]) - 97] -= 1
            if i >= m:
                cnt[ord(s[i - m]) - 97] += 1
            if i >= m - 1:
                if all(x == 0 for x in cnt):
                    ans.append(i - m + 1)
        return ans


def main() -> None:
    s = input().strip()
    p = input().strip()
    ans = Solution().findAnagrams(s, p)
    print(*ans)


if __name__ == "__main__":
    main()
