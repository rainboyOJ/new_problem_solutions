import heapq
import sys
from array import array


MAX_BIT = 31
input = sys.stdin.buffer.readline
n, required = map(int, input().split())
values = map(int, input().split())
left = array("i", [0])
right = array("i", [0])
count = array("i", [0])


def clone(node):
    left.append(left[node])
    right.append(right[node])
    count.append(count[node])
    return len(count) - 1


def insert(previous_root, value):
    root = clone(previous_root)
    count[root] += 1
    previous, current = previous_root, root
    for bit in range(MAX_BIT, -1, -1):
        if value >> bit & 1:
            child = clone(right[previous])
            right[current] = child
            previous = right[previous]
        else:
            child = clone(left[previous])
            left[current] = child
            previous = left[previous]
        current = child
        count[current] += 1
    return root


def kth_xor(root, value, rank):
    answer = 0
    for bit in range(MAX_BIT, -1, -1):
        wanted = left[root] if value >> bit & 1 else right[root]
        wanted_count = count[wanted]
        if rank <= wanted_count:
            answer |= 1 << bit
            root = wanted
        else:
            rank -= wanted_count
            root = right[root] if value >> bit & 1 else left[root]
    return answer


prefix_xor = array("I", [0])
for value in values:
    prefix_xor.append(prefix_xor[-1] ^ value)

roots = array("i", [0, insert(0, 0)])
for value in prefix_xor[1:]:
    roots.append(insert(roots[-1], value))

heap = [(-kth_xor(roots[end], prefix_xor[end], 1), end, 1)
        for end in range(1, n + 1)]
heapq.heapify(heap)
answer = 0

for _ in range(required):
    negative, end, rank = heapq.heappop(heap)
    answer -= negative
    if rank < end:
        rank += 1
        heapq.heappush(heap, (-kth_xor(roots[end], prefix_xor[end], rank), end, rank))

print(answer)
