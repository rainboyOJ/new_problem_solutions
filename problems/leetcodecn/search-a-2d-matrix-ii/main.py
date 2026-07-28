#!/usr/bin/env python3
from typing import List


class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        i, j = 0, n - 1
        while i < m and j >= 0:
            if matrix[i][j] == target:
                return True
            if matrix[i][j] < target:
                i += 1
            else:
                j -= 1
        return False


def main() -> None:
    m, n, t = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(m)]
    print(Solution().searchMatrix(a, t))


if __name__ == "__main__":
    main()
