MAX_N = 20
up = [[0] * (MAX_N + 1) for _ in range(MAX_N + 1)]
down = [[0] * (MAX_N + 1) for _ in range(MAX_N + 1)]
up[1][1] = down[1][1] = 1

for length in range(2, MAX_N + 1):
    for rank in range(1, length + 1):
        up[length][rank] = sum(down[length - 1][next_rank - 1] for next_rank in range(rank + 1, length + 1))
        down[length][rank] = sum(up[length - 1][next_rank] for next_rank in range(1, rank))


def continuation_count(length: int, rank: int, relation_to_next: int) -> int:
    if length == 1:
        return 1
    return up[length][rank] if relation_to_next > 0 else down[length][rank]


for _ in range(int(input())):
    length, catalogue_number = map(int, input().split())
    remaining = list(range(1, length + 1))
    answer = []
    previous_relation = None
    while remaining:
        for index, value in enumerate(remaining):
            if previous_relation is not None:
                relation = 1 if answer[-1] < value else -1
                if relation == previous_relation:
                    continue
            else:
                relation = None
            rank = index + 1
            rest_length = len(remaining)
            if rest_length == 1:
                count = 1
            elif relation is None:
                count = up[rest_length][rank] + down[rest_length][rank]
            else:
                count = continuation_count(rest_length, rank, -relation)
            if catalogue_number > count:
                catalogue_number -= count
                continue
            answer.append(value)
            remaining.pop(index)
            previous_relation = relation
            break
    print(*answer)
