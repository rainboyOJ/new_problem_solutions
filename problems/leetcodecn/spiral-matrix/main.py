#!/usr/bin/env python3
from typing import List


class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        if not matrix:
            return []
        t, b, l, r = 0, len(matrix) - 1, 0, len(matrix[0]) - 1
        ans = []
        while t <= b and l <= r:
            for j in range(l, r + 1):
                ans.append(matrix[t][j])
            t += 1
            for i in range(t, b + 1):
                ans.append(matrix[i][r])
            r -= 1
            if t <= b:
                for j in range(r, l - 1, -1):
                    ans.append(matrix[b][j])
                b -= 1
            if l <= r:
                for i in range(b, t - 1, -1):
                    ans.append(matrix[i][l])
                l += 1
        return ans


def main() -> None:
    m, n = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(m)]
    print(*Solution().spiralOrder(a))


if __name__ == "__main__":
    main()
