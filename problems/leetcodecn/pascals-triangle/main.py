#!/usr/bin/env python3
from typing import List


class Solution:
    def generate(self, n: int) -> List[List[int]]:
        ans = []
        for i in range(n):
            row = [1] * (i + 1)
            for j in range(1, i):
                row[j] = ans[-1][j - 1] + ans[-1][j]
            ans.append(row)
        return ans


def main():
    n = int(input())
    for v in Solution().generate(n):
        print(*v)


if __name__ == "__main__":
    main()
