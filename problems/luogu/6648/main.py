import sys
from array import array


input = sys.stdin.buffer.readline
n, target_size = map(int, input().split())
maximum = [array("i", map(int, input().split())) for _ in range(n)]
size = 1

while size * 2 < target_size:
    next_size = size * 2
    half = size // 2
    maximum = [
        array("i", map(max, zip(
            maximum[i],
            maximum[i + size][:i + 1],
            maximum[i + size][size:size + i + 1],
            maximum[i + half][:i + 1],
            maximum[i + half][half:half + i + 1],
            maximum[i + size][half:half + i + 1],
        )))
        for i in range(n - next_size + 1)
    ]
    size = next_size

offset = target_size - size
half = offset // 2
answer = sum(
    sum(map(max, zip(
        maximum[i],
        maximum[i + offset][:i + 1],
        maximum[i + offset][offset:offset + i + 1],
        maximum[i + half][:i + 1],
        maximum[i + half][half:half + i + 1],
        maximum[i + offset][half:half + i + 1],
    )))
    for i in range(n - target_size + 1)
)
print(answer)
