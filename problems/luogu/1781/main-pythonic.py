n = int(input())
best_index, best_votes = 1, input().strip()
for index in range(2, n + 1):
    votes = input().strip()
    if (len(votes), votes) > (len(best_votes), best_votes):
        best_index, best_votes = index, votes
print(best_index)
print(best_votes)
