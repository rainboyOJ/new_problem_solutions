import sys
from bisect import bisect_left
from math import inf


data = list(map(int, sys.stdin.buffer.read().split()))
m, n = data[:2]
schools = sorted(data[2:2 + m])
students = data[2 + m:2 + m + n]


def dissatisfaction(score):
    index = bisect_left(schools, score)
    lower = score - schools[index - 1] if index else inf
    upper = schools[index] - score if index < m else inf
    return min(lower, upper)


print(sum(map(dissatisfaction, students)))
