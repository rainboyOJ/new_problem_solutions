n = int(input())
best_index = 1
best_votes = input().strip()

for index in range(2, n + 1):
    votes = input().strip()
    if len(votes) > len(best_votes) or (
        len(votes) == len(best_votes) and votes > best_votes
    ):
        best_index = index
        best_votes = votes

print(best_index)
print(best_votes)
