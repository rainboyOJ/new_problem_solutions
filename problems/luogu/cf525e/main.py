import math
import sys
from collections import defaultdict


n, sticker_limit, target = map(int, sys.stdin.buffer.readline().split())
values = list(map(int, sys.stdin.buffer.readline().split()))
middle = n // 2
factorials = [math.factorial(value) if value <= 18 else None for value in values]
left_count = [defaultdict(int) for _ in range(sticker_limit + 1)]


def enumerate_left(index, end, total, stickers):
    if total > target or stickers > sticker_limit:
        return
    if index == end:
        left_count[stickers][total] += 1
        return
    enumerate_left(index + 1, end, total, stickers)
    enumerate_left(index + 1, end, total + values[index], stickers)
    factorial = factorials[index]
    if factorial is not None:
        enumerate_left(index + 1, end, total + factorial, stickers + 1)


enumerate_left(0, middle, 0, 0)
answer = 0


def enumerate_right(index, total, stickers):
    global answer
    if total > target or stickers > sticker_limit:
        return
    if index == n:
        needed = target - total
        answer += sum(left_count[used].get(needed, 0)
                      for used in range(sticker_limit - stickers + 1))
        return
    enumerate_right(index + 1, total, stickers)
    enumerate_right(index + 1, total + values[index], stickers)
    factorial = factorials[index]
    if factorial is not None:
        enumerate_right(index + 1, total + factorial, stickers + 1)


enumerate_right(middle, 0, 0)
print(answer)
