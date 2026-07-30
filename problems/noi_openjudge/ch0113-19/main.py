from bisect import bisect_right

point_count = int(input())
demands = []
edge_lengths = []
for _ in range(point_count):
    demand, edge_length = map(int, input().split())
    demands.append(demand)
    edge_lengths.append(edge_length)

positions = [0]
for edge_length in edge_lengths[:-1]:
    positions.append(positions[-1] + edge_length)
perimeter = sum(edge_lengths)
coordinates = positions + [position + perimeter for position in positions]
weights = demands * 2
prefix_weight = [0]
prefix_weighted_coordinate = [0]
for coordinate, weight in zip(coordinates, weights):
    prefix_weight.append(prefix_weight[-1] + weight)
    prefix_weighted_coordinate.append(prefix_weighted_coordinate[-1] + coordinate * weight)


def interval_sum(prefix: list[int], left: int, right: int) -> int:
    return prefix[right] - prefix[left]


best_index = 0
best_cost = None
for index, position in enumerate(positions):
    middle = bisect_right(coordinates, position + perimeter / 2, lo=index, hi=index + point_count)
    # (position, position + half] 走顺时针；其余点走逆时针。
    forward_weight = interval_sum(prefix_weight, index + 1, middle)
    forward_coordinates = interval_sum(prefix_weighted_coordinate, index + 1, middle)
    backward_weight = interval_sum(prefix_weight, middle, index + point_count)
    backward_coordinates = interval_sum(prefix_weighted_coordinate, middle, index + point_count)
    cost = forward_coordinates - position * forward_weight
    cost += (position + perimeter) * backward_weight - backward_coordinates
    if best_cost is None or cost < best_cost:
        best_index, best_cost = index, cost

print(f"{best_index},{best_cost}")
