import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n, need = data[:2]
heights = data[2:2 + n]


def enough(cut):
    return sum(max(0, height - cut) for height in heights) >= need


def check(cut):
    """切割高度 cut 是否失败（木材不足 need）。false ... false true ... true"""
    return not enough(cut)


# 在 [0, max + 1] 中找第一个失败位置，max + 1 是虚拟失败位置。
# 答案 = 失败位置 - 1，即最后一个可行高度。
left, right = 0, max(heights) + 1
while left < right:
    middle = (left + right) // 2
    if check(middle):
        right = middle
    else:
        left = middle + 1

print(left - 1)
