from functools import lru_cache


@lru_cache(None)
def count_outputs(waiting, stack_size):
    if waiting == 0:
        return 1

    answer = count_outputs(waiting - 1, stack_size + 1)
    if stack_size > 0:
        answer += count_outputs(waiting, stack_size - 1)
    return answer


n = int(input())
print(count_outputs(n, 0))
