import sys
from array import array


input = sys.stdin.buffer.readline
n, limit = map(int, input().split())
values = [int(input()) for _ in range(n)]
highest_bit = max(limit, max(values)).bit_length() - 1
child_zero = array("i", [0, 0])
child_one = array("i", [0, 0])
count = array("i", [0, 0])

for value in values:
    node = 1
    count[node] += 1
    for bit in range(highest_bit, -1, -1):
        children = child_one if value >> bit & 1 else child_zero
        if not children[node]:
            children[node] = len(count)
            child_zero.append(0)
            child_one.append(0)
            count.append(0)
        node = children[node]
        count[node] += 1


def solve(node, bit):
    if not node or bit < 0:
        return count[node]
    zero, one = child_zero[node], child_one[node]
    if limit >> bit & 1:
        return max(count[zero] + solve(one, bit - 1),
                   count[one] + solve(zero, bit - 1))
    return max(solve(zero, bit - 1), solve(one, bit - 1))


print(solve(1, highest_bit))
