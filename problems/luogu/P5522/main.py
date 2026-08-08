import sys
from bisect import bisect_right


input = sys.stdin.buffer.readline
n, strings, operations = map(int, input().split())
size = 1
while size < strings:
    size <<= 1
zero = [0] * (2 * size)
one = [0] * (2 * size)


def encode(text):
    zeros = ones = 0
    for index, char in enumerate(text):
        bit = 1 << index
        if char == 48:
            zeros |= bit
        elif char == 49:
            ones |= bit
    return zeros, ones


for index in range(strings):
    zero[size + index], one[size + index] = encode(input().strip())
for index in range(size - 1, 0, -1):
    zero[index] = zero[index * 2] | zero[index * 2 + 1]
    one[index] = one[index * 2] | one[index * 2 + 1]

answers = 0
for _ in range(operations):
    operation = input().split()
    if operation[0] == b'1':
        position = int(operation[1]) - 1
        zero[size + position], one[size + position] = encode(operation[2])
        node = (size + position) // 2
        while node:
            zero[node] = zero[node * 2] | zero[node * 2 + 1]
            one[node] = one[node * 2] | one[node * 2 + 1]
            node //= 2
        continue
    left, right = int(operation[1]) - 1 + size, int(operation[2]) + size
    zeros = ones = 0
    while left < right:
        if left & 1:
            zeros |= zero[left]
            ones |= one[left]
            left += 1
        if right & 1:
            right -= 1
            zeros |= zero[right]
            ones |= one[right]
        left //= 2
        right //= 2
    answers ^= 0 if zeros & ones else 1 << (n - (zeros | ones).bit_count())
print(answers)
