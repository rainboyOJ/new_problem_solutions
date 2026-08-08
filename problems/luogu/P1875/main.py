import sys
from heapq import heapify, heappop, heappush


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
price = data[1:n + 1]
recipes = [tuple(data[index:index + 3]) for index in range(n + 1, len(data), 3)]
by_ingredient = [[] for _ in range(n)]
for index, (first, second, result) in enumerate(recipes):
    by_ingredient[first].append(index)
    if second != first:
        by_ingredient[second].append(index)

distance = price[:]
heap = [(value, potion) for potion, value in enumerate(distance)]
heapify(heap)
while heap:
    current, potion = heappop(heap)
    if current != distance[potion]:
        continue
    for recipe_index in by_ingredient[potion]:
        first, second, result = recipes[recipe_index]
        candidate = distance[first] + distance[second]
        if candidate < distance[result]:
            distance[result] = candidate
            heappush(heap, (candidate, result))

ways = [0] * n
recipes_by_result = [[] for _ in range(n)]
for first, second, result in recipes:
    recipes_by_result[result].append((first, second))
for potion in sorted(range(n), key=distance.__getitem__):
    ways[potion] = price[potion] == distance[potion]
    ways[potion] += sum(ways[first] * ways[second] for first, second in recipes_by_result[potion]
                        if distance[first] + distance[second] == distance[potion])
print(distance[0], ways[0])
