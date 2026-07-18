import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, segment_limit = data[:2]
numbers = data[2:2 + n]

def possible(maximum_sum):
    segments = 1
    current_sum = 0
    for number in numbers:
        if current_sum + number <= maximum_sum:
            current_sum += number
        else:
            segments += 1
            current_sum = number
    return segments <= segment_limit

left, right = max(numbers), sum(numbers)
while left < right:
    middle = (left + right) // 2
    if possible(middle):
        right = middle
    else:
        left = middle + 1

print(left)
