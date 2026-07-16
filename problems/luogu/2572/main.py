import sys
from array import array


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
values = list(map(int, input().split()))
ones = array("i", [0]) * (4 * n)
one_prefix = array("i", [0]) * (4 * n)
one_suffix = array("i", [0]) * (4 * n)
one_best = array("i", [0]) * (4 * n)
zeros = array("i", [0]) * (4 * n)
zero_prefix = array("i", [0]) * (4 * n)
zero_suffix = array("i", [0]) * (4 * n)
zero_best = array("i", [0]) * (4 * n)
assigned = array("b", [-1]) * (4 * n)
flipped = bytearray(4 * n)


def apply_assign(node, value, length):
    assigned[node] = value
    flipped[node] = 0
    if value:
        ones[node] = length
        one_prefix[node] = one_suffix[node] = one_best[node] = length
        zeros[node] = zero_prefix[node] = zero_suffix[node] = zero_best[node] = 0
    else:
        zeros[node] = length
        zero_prefix[node] = zero_suffix[node] = zero_best[node] = length
        ones[node] = one_prefix[node] = one_suffix[node] = one_best[node] = 0


def apply_flip(node):
    ones[node], zeros[node] = zeros[node], ones[node]
    one_prefix[node], zero_prefix[node] = zero_prefix[node], one_prefix[node]
    one_suffix[node], zero_suffix[node] = zero_suffix[node], one_suffix[node]
    one_best[node], zero_best[node] = zero_best[node], one_best[node]
    if assigned[node] != -1:
        assigned[node] ^= 1
    else:
        flipped[node] ^= 1


def pull(node, left_length, right_length):
    left, right = node * 2, node * 2 + 1
    ones[node] = ones[left] + ones[right]
    one_prefix[node] = one_prefix[left] + one_prefix[right] if one_prefix[left] == left_length else one_prefix[left]
    one_suffix[node] = one_suffix[right] + one_suffix[left] if one_suffix[right] == right_length else one_suffix[right]
    one_best[node] = max(one_best[left], one_best[right], one_suffix[left] + one_prefix[right])
    zeros[node] = zeros[left] + zeros[right]
    zero_prefix[node] = zero_prefix[left] + zero_prefix[right] if zero_prefix[left] == left_length else zero_prefix[left]
    zero_suffix[node] = zero_suffix[right] + zero_suffix[left] if zero_suffix[right] == right_length else zero_suffix[right]
    zero_best[node] = max(zero_best[left], zero_best[right], zero_suffix[left] + zero_prefix[right])


def build(node, left, right):
    if left == right:
        apply_assign(node, values[left - 1], 1)
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    pull(node, middle - left + 1, right - middle)


def push(node, left, right):
    if left == right:
        assigned[node] = -1
        flipped[node] = 0
        return
    middle = (left + right) // 2
    left_child, right_child = node * 2, node * 2 + 1
    if assigned[node] != -1:
        apply_assign(left_child, assigned[node], middle - left + 1)
        apply_assign(right_child, assigned[node], right - middle)
        assigned[node] = -1
    if flipped[node]:
        apply_flip(left_child)
        apply_flip(right_child)
        flipped[node] = 0


def update(node, left, right, query_left, query_right, kind):
    if query_left <= left and right <= query_right:
        if kind == 2:
            apply_flip(node)
        else:
            apply_assign(node, kind, right - left + 1)
        return
    push(node, left, right)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right, kind)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right, kind)
    pull(node, middle - left + 1, right - middle)


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return ones[node], one_prefix[node], one_suffix[node], one_best[node], right - left + 1
    push(node, left, right)
    middle = (left + right) // 2
    result = None
    if query_left <= middle:
        result = query(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        right_result = query(node * 2 + 1, middle + 1, right, query_left, query_right)
        if result is None:
            result = right_result
        else:
            left_sum, left_prefix, left_suffix, left_best, left_length = result
            right_sum, right_prefix, right_suffix, right_best, right_length = right_result
            result = (left_sum + right_sum,
                      left_prefix + right_prefix if left_prefix == left_length else left_prefix,
                      right_suffix + left_suffix if right_suffix == right_length else right_suffix,
                      max(left_best, right_best, left_suffix + right_prefix),
                      left_length + right_length)
    return result


build(1, 1, n)
answers = []
for _ in range(operations):
    kind, left, right = map(int, input().split())
    left += 1
    right += 1
    if kind < 3:
        update(1, 1, n, left, right, kind)
    else:
        result = query(1, 1, n, left, right)
        answers.append(str(result[0] if kind == 3 else result[3]))
print("\n".join(answers))
