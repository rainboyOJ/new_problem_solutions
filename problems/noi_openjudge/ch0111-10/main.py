river_length, rock_count, removal_limit = map(int, input().split())
rocks = [0] + [int(input()) for _ in range(rock_count)] + [river_length]


def can_keep_minimum_distance(distance: int) -> bool:
    removed = 0
    previous = 0
    for position in rocks[1:]:
        if position - previous < distance:
            removed += 1
        else:
            previous = position
    # 最后一次不足时，计数等价于删去最后保留的石头；后面已无石头，不影响计数。
    return removed <= removal_limit


low, high = 1, river_length
while low < high:
    middle = (low + high + 1) // 2
    if can_keep_minimum_distance(middle):
        low = middle
    else:
        high = middle - 1

print(low)
