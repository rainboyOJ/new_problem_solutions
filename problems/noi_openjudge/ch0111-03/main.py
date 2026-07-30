square_side = int(input())
rectangle_count = int(input())
rectangles = [tuple(map(int, input().split())) for _ in range(rectangle_count)]


def left_area(x: int) -> int:
    area = 0
    for left, _, width, height in rectangles:
        area += max(0, min(width, x - left)) * height
    return area


total_area = sum(width * height for _, _, width, height in rectangles)

# 先找左侧面积首次不少于右侧面积的位置。
low, high = 0, square_side
while low < high:
    middle = (low + high) // 2
    if left_area(middle) * 2 >= total_area:
        high = middle
    else:
        low = middle + 1

minimum_left_area = left_area(low)
# 同样的最小面积可能对应多个整数横坐标，取其中最大的一个。
low, high = low, square_side
while low < high:
    middle = (low + high + 1) // 2
    if left_area(middle) <= minimum_left_area:
        low = middle
    else:
        high = middle - 1

print(low)
