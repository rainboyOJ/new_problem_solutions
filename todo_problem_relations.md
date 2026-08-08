# 题目关系 pre/common 补全交接

目标：继续为 `problems/<oj>/<problem_id>/index.md` 的 frontmatter 补全 `pre` / `common`，用于后续题目学习图。

## 当前状态

- 已创建并提交关系维护 skill：`.agents/skills/oj-problem-relation-writer/SKILL.md`
- 已创建并提交校验脚本：`scripts/problem-analysis-tools/check_relations.py`
- 当前工作区已经把历史旧格式 `pre: - oj,pid` 清理为新格式或空数组。
- 当前工作区已经完成第一批 SCC / 强连通分量关系补全。
- 当前改动尚未提交。

交接时必须先运行：

```bash
python3 scripts/problem-analysis-tools/check_relations.py --all
```

当前期望结果：

```text
检查题目数：172
通过：关系字段符合当前规范。
```

## 关系字段规范

只维护 frontmatter 中的两个字段：

```yaml
pre:
  - oj: "luogu"
    problem_id: "P3387"
    reason: "需要先掌握 Tarjan 缩点，再理解当前题的 DAG DP。"
common:
  - oj: "POJ"
    problem_id: "2186"
    reason: "同为受欢迎的牛模型，缩点后判断唯一汇点 SCC。"
```

规则：

- `pre`：当前题的前置题，方向是 `pre_problem -> current_problem`。
- `common`：相似题，不表达难度方向。
- 每条关系都要写 `reason`。
- 不使用 `pid`，统一使用 `problem_id`。
- `oj` 和 `problem_id` 必须和目标题 `index.md` frontmatter 一致。
- 只写真正高置信度关系。
- 不能只因为 tag 相同就写 `common`。
- 不能编造不存在的题目。
- 低置信度候选写到 `problem-relation-workspace/candidates.md`，不要写入正式 frontmatter。

## 已完成：SCC / 强连通分量批次

本批已经写入关系的题目：

```text
problems/hdu/1269/index.md
problems/luogu/P2863/index.md
problems/luogu/P3387/index.md
problems/luogu/P2341/index.md
problems/poj/2186/index.md
problems/luogu/P2746/index.md
problems/hdu/3836/index.md
problems/hdu/1827/index.md
problems/hdu/3072/index.md
problems/hdu/3639/index.md
problems/luogu/P2272/index.md
problems/luogu/P2515/index.md
problems/luogu/P1407/index.md
```

本批刻意没有处理这些 Tarjan 相关但不是 SCC 的题：

```text
problems/poj/1144/index.md
problems/poj/1523/index.md
problems/luogu/P5058/index.md
problems/luogu/P3225/index.md
problems/poj/2942/index.md
problems/OpenJ_Bailian/3091/index.md
problems/hdu/3394/index.md
```

这些应放到后面的“割点 / 双连通分量”批次。

## 推荐后续批次

### P0：割点 / 双连通分量

建议下一批先做这个，因为它和 SCC 同属 Tarjan 体系，但语义不同，适合单独成组。

候选：

```text
POJ 1144 Network
POJ 1523 SPF
luogu P5058 嗅探器
luogu P3225 矿场搭建
POJ 2942 Knights of the Round Table
OpenJ_Bailian 3091 Road Construction
HDU 3394 Railway
```

建议判断：

- 割点模板题可以互为 `common`，或作为更复杂割点题的 `pre`。
- 点双 / 边双不要混成同一个 common，除非题解明确模型一致。
- POJ 2942 还包含二分图染色，可能需要 `pre` 指向点双基础题和二分图染色基础题。

### P1：欧拉路 / 欧拉回路

候选：

```text
HDU 1878
HDU 1116
HDU 5883
OpenJ_Bailian 1041
OpenJ_Bailian 1300
OpenJ_Bailian 1392
OpenJ_Bailian 2513
luogu P1127
luogu P1341
```

建议判断：

- 先区分无向欧拉回路、有向欧拉路径、字典序输出路径。
- 模板题作为 `pre`，同模型不同输出约束作为 `common`。

### P1：二分 / 二分答案

候选：

```text
POJ 3122
POJ 2976
OpenJ_Bailian 4135
atcoder abc248_d
luogu P1678
luogu P1873
luogu P1419
luogu P3199
```

建议判断：

- 普通二分查找、二分答案、分数规划要分开。
- `POJ 2976`、`luogu P1419`、`luogu P3199` 更接近分数规划，不要和普通二分强行 common。

### P1：网络流 / 费用流 / 最小割

候选：

```text
HDU 3549
luogu P2763
luogu P2764
luogu P2765
luogu P2766
luogu P2774
luogu P4001
luogu P4013
luogu P4014
luogu P4015
luogu P4016
luogu P2053
luogu P3358
luogu P3749
```

建议判断：

- 最大流、二分图匹配、最小割、费用流、最大权闭合子图分成子批次。
- 费用流模板题可以作为多道费用流建模题的 `pre`。
- 最小割建模题不要直接和费用流题写 common。

### P2：单调队列 / 单调栈

候选：

```text
luogu P2032
luogu P1714
luogu P2627
luogu P2629
luogu P1198
luogu P2947
```

建议判断：

- 滑动窗口最大值是基础 `pre`。
- 前缀和 + 单调队列优化与纯窗口题不要只因 tag 相同就 common。

### P2：DP / 背包 / 树形 DP

候选较多，建议拆小批：

```text
HDU 1003
HDU 2602
POJ 3176
OpenJ_Bailian 2506
OpenJ_Bailian 1651
luogu P2014
luogu P2515
luogu P1642
luogu P4322
```

建议判断：

- 线性 DP、背包、区间 DP、树形 DP 分开处理。
- `luogu P2515` 已经写入 `P2014` 和 `P3387` 作为 `pre`。

## 每批标准工作流

1. 用 `rg` 找候选题：

```bash
rg -n "割点|点双|边双|欧拉|费用流|最小割|单调队列" problems -g 'index.md'
```

2. 读取候选题的 frontmatter、题意、思路、代码引用。

3. 只写高置信度关系：

- 基础模板题 -> 进阶题：写 `pre`
- 几乎同题或同一训练模型：写 `common`
- 只是同 tag 或表面相似：不写，记录候选

4. 修改 frontmatter 后运行：

```bash
python3 scripts/problem-analysis-tools/check_relations.py --all
git diff --check
```

5. 最终回复中报告：

- 本批处理的主题
- 修改了哪些题
- 写入了哪些 `pre`
- 写入了哪些 `common`
- 哪些候选没有写入以及原因
- 校验结果

## 注意事项

- 当前有未跟踪文件：`codex_resume`、`problems/luogu/P1009/`、`work2_.md`，不要误删。
- 当前分支在远端基础上已有一个本地 commit ahead 1。
- 不要在没有用户要求时 commit。
- 不要把 `problem-relation-workspace/` 加入提交，它已经被 `.gitignore` 忽略。
- 不要为了“补全所有题”而低质量批量生成关系。
