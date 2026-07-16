import sys
from collections import defaultdict


tokens = sys.stdin.buffer.read().split()
separator = tokens.index(b".")
primitives_by_length = defaultdict(set)
for primitive in tokens[:separator]:
    primitives_by_length[len(primitive)].add(primitive)
sequence = b"".join(tokens[separator + 1:])

reachable = bytearray(len(sequence) + 1)
reachable[0] = 1
answer = 0
for start in range(len(sequence)):
    if not reachable[start]:
        continue
    for length, primitives in primitives_by_length.items():
        end = start + length
        if sequence[start:end] in primitives:
            reachable[end] = 1
            answer = max(answer, end)
print(answer)
