from collections import Counter

counts = Counter(input())
character = min(counts, key=lambda item: (-counts[item], item))

print(character, counts[character])
