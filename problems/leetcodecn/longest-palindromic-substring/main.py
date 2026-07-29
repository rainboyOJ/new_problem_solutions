#!/usr/bin/env python3
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        start = length = 0

        def expand(l, r):
            nonlocal start, length
            while l >= 0 and r < n and s[l] == s[r]:
                l -= 1
                r += 1
            if r - l - 1 > length:
                start = l + 1
                length = r - l - 1

        for i in range(n):
            expand(i, i)
            expand(i, i + 1)
        return s[start : start + length]


def main():
    print(Solution().longestPalindrome(input().strip()))


if __name__ == "__main__":
    main()
