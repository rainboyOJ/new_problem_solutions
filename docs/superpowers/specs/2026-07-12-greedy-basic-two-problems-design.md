# Greedy Basic Problem Set Additions Design

## Goal

Add Luogu P13256 and P10483 to `problem-sets/greedy-basic.md` at positions that preserve a clear learning progression and accurately describe the role of greedy reasoning in each problem.

## Scope

Modify only:

- `problem-sets/greedy-basic.md`

Do not create local problem directories, write solutions, change problem-set rendering code, or modify unrelated problem sets.

## Problem Classification

### P13256 Data Packing

Each disc holds at most two files. After sorting, process the largest remaining file:

- pair it with the smallest remaining file when they fit;
- otherwise place the largest file alone.

This is the same two-pointer capacity-pairing model as P1094 and belongs immediately after P1094 in the existing “双指针配对贪心” section.

Use this entry:

```markdown
- [ ] [[problem: luogu,P13256]]
  - 模型：每组最多两个元素的容量配对。
  - 贪心点：每次处理最大的文件；若它能和当前最小文件同盘就配对，否则最大的文件只能单独占一盘。
```

The section order becomes P1094, P13256, P4995.

### P10483 小猫爬山

Each cable car may carry more than two cats, so the two-pointer pairing rule does not solve the general packing problem. With `N <= 18`, the accepted model is descending-order DFS with branch-and-bound:

- sorting cats from heavy to light makes capacity constraints take effect earlier;
- DFS still explores the necessary assignments and provides correctness;
- the greedy order improves search efficiency but does not independently prove optimality.

Create a new section immediately after the two-pointer section:

```markdown
## 六、贪心顺序辅助搜索

核心思路：当局部选择不能直接保证全局最优时，仍可用贪心顺序优先处理约束最强的对象，减少搜索分支；最终正确性来自完整搜索。

- [ ] [[problem: luogu,P10483]]
  - 模型：降序搜索 + DFS 分支限界。
  - 贪心点：先安排更重的小猫，让容量约束尽早生效；但降序只优化搜索顺序，最优性由 DFS 枚举保证。
```

This section teaches the boundary between a complete greedy solution and a greedy search order. Do not classify P10483 as a two-pointer greedy problem.

## Section Renumbering

Insert the new section as section six. Renumber the existing later sections without changing their content:

- 邻项交换排序模型: 六 -> 七
- 单调栈贪心: 七 -> 八
- 连续序列分组贪心: 八 -> 九
- 有限资源低成本选取模型: 九 -> 十

Keep “复盘要求” unnumbered.

## Missing Local Problems

Neither problem currently has a local `problems/luogu/<id>/` directory. This is allowed by the existing problem-set renderer: each task is displayed as disabled text with the “未收录” badge. The renderer does not create an external Luogu link for a missing local problem.

Do not fetch or scaffold either problem as part of this change.

## Verification

1. Confirm P13256 and P10483 each appear exactly once in `greedy-basic.md`.
2. Confirm P13256 is between P1094 and P4995.
3. Confirm P10483 is in the new section immediately after the two-pointer section.
4. Confirm numbered sections run continuously from one through ten.
5. Run the repository problem-set and Markdown-link tests.
6. Render or request `/problem-sets/greedy-basic` and confirm both tasks appear as disabled missing-local-problem entries with the “未收录” badge rather than broken markup.
