student_count, planned_count = map(int, input().split())
candidates = [tuple(map(int, input().split())) for _ in range(student_count)]

candidates.sort(key=lambda candidate: (-candidate[1], candidate[0]))
cutoff_index = int(planned_count * 1.5) - 1
cutoff_score = candidates[cutoff_index][1]
qualified = [candidate for candidate in candidates if candidate[1] >= cutoff_score]

print(cutoff_score, len(qualified))
for candidate_id, score in qualified:
    print(candidate_id, score)
