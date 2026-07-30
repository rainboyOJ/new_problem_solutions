from math import pi

pie_count, friend_count = map(int, input().split())
areas = [pi * radius * radius for radius in map(int, input().split())]
needed_pieces = friend_count + 1


def can_share(area: float) -> bool:
    return sum(int(pie_area / area) for pie_area in areas) >= needed_pieces


low, high = 0.0, max(areas)
for _ in range(100):
    middle = (low + high) / 2
    if can_share(middle):
        low = middle
    else:
        high = middle

print(f"{low:.3f}")
