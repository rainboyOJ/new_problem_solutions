from functools import cache


@cache
def dfs(waiting, stack_size):
    if waiting == 0:
        return 1
    answer = dfs(waiting - 1, stack_size + 1)
    if stack_size:
        answer += dfs(waiting, stack_size - 1)
    return answer


print(dfs(int(input()), 0))
