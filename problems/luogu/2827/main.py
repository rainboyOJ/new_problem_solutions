import sys
from array import array


data = iter(map(int, sys.stdin.buffer.read().split()))
n, seconds, increase, numerator, denominator, interval = (next(data) for _ in range(6))
initial = sorted((next(data) for _ in range(n)), reverse=True)
first = array("q")
second = array("q")
heads = [0, 0, 0]
cut_output = []


def pop_maximum():
    candidates = (initial[heads[0]] if heads[0] < len(initial) else -10**30,
                  first[heads[1]] if heads[1] < len(first) else -10**30,
                  second[heads[2]] if heads[2] < len(second) else -10**30)
    queue = max(range(3), key=candidates.__getitem__)
    heads[queue] += 1
    return candidates[queue]


for current_second in range(1, seconds + 1):
    length = pop_maximum() + (current_second - 1) * increase
    if current_second % interval == 0:
        cut_output.append(str(length))
    left_part = length * numerator // denominator
    offset = current_second * increase
    first.append(left_part - offset)
    second.append(length - left_part - offset)

print(" ".join(cut_output))
final_output = []
offset = seconds * increase
for rank in range(1, n + seconds + 1):
    length = pop_maximum() + offset
    if rank % interval == 0:
        final_output.append(str(length))
print(" ".join(final_output))
