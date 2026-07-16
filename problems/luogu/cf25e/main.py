import sys
from array import array
from itertools import permutations


def merge(left, right):
    if right in left:
        return left
    if left in right:
        return right
    combined = right + b"\0" + left
    prefix = array("i", [0]) * len(combined)
    j = 0
    for i in range(1, len(combined)):
        while j and combined[i] != combined[j]:
            j = prefix[j - 1]
        if combined[i] == combined[j]:
            j += 1
        prefix[i] = j
    return left + right[prefix[-1]:]


strings = sys.stdin.buffer.read().split()
print(min(len(merge(merge(first, second), third))
          for first, second, third in permutations(strings)))
