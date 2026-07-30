from collections import Counter, defaultdict

post_count = int(input())
mentioned_count = Counter()
mentioners = defaultdict(set)

for _ in range(post_count):
    sender, count, *mentioned = map(int, input().split())
    for person in mentioned[:count]:
        mentioned_count[person] += 1
        mentioners[person].add(sender)

focus = max(mentioned_count, key=mentioned_count.get)
print(focus)
print(*sorted(mentioners[focus]))
