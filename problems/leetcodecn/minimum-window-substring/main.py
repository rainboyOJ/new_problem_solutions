#!/usr/bin/env python3
from collections import defaultdict


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        need = defaultdict(int)
        for ch in t:
            need[ch] += 1
        missing = len(need)
        l = start = 0
        min_len = float("inf")
        for r, ch in enumerate(s):
            if ch in need:
                need[ch] -= 1
                if need[ch] == 0:
                    missing -= 1
            while missing == 0:
                if r - l + 1 < min_len:
                    min_len = r - l + 1
                    start = l
                left_ch = s[l]
                if left_ch in need:
                    need[left_ch] += 1
                    if need[left_ch] > 0:
                        missing += 1
                l += 1
        return "" if min_len == float("inf") else s[start:start + min_len]


def main() -> None:
    s = input().strip()
    t = input().strip()
    print(Solution().minWindow(s, t))


if __name__ == "__main__":
    main()
