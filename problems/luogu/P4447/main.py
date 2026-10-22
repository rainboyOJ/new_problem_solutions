"""P4447 [AHOI2018初中组] 分组

把每个组看成一条「链」：链上的实力值依次加 1，不跳也不重复。
于是「分组」等价于「把每个实力值的队员分配到若干条链上」。

按实力值从小到大处理，因为值 x 的队员只能接到「以 x-1 结尾」的链上，
接不上就只能以 x 新开一条长度为 1 的链。决策顺序被值域唯一确定，可以贪心。

三条规则，按执行顺序编号（前两条用交换论证证明不会让答案变差）：
  一、实力值不连续时，前一段的链全部冻结，必须当场结算
  二、有多条链可接时，接最短的 —— 短链最可能成为答案，优先给它增长机会
  三、链比人多的部分接不上，只能冻结；冻结的应当是其中最长的那些

实现上用 defaultdict(list) 给每个「结尾实力值」配一个小根堆存链长：
堆顶总是以该值结尾的最短链，天然满足规则二（先取最短）
和规则三（剩下的都更长，冻结它们）。
规则一在逐个处理时自然消解：值 x-1 的堆为空即说明断档，不必显式判断。
"""

from collections import defaultdict
import heapq
import sys


def main() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    abilities = data[1:1 + n]
    abilities.sort()

    # chains[v] = 以实力值 v 结尾的所有链长，小根堆维护，堆顶是最短的那条
    chains = defaultdict(list)

    # 链长的最小值就是答案，先取最坏上界 n
    answer = n

    for x in abilities:
        if chains[x - 1]:
            # 规则一：能接就接最短的（堆顶），长度加 1 后挂到 x 这端
            length = heapq.heappop(chains[x - 1]) + 1
        else:
            # 接不上任何旧链，只能以 x 新开一条长度为 1 的链
            length = 1
        heapq.heappush(chains[x], length)

    # 所有值的队员都安排完了，堆里剩下的每条链长度都已定格，
    # 逐个取最小值即为答案。
    # 注意：同一实力值不会出现在两个不同的 x 上，所以每个链只被统计一次。
    for heap in chains.values():
        for length in heap:
            if length < answer:
                answer = length

    print(answer)


if __name__ == "__main__":
    main()
