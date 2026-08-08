# OJ 写题能力提升 TODO

目标：让本项目从“题解文章集合”逐步变成“读题、写题、验证、复盘”的长期训练系统。

## P0：先修基础设施（已完成）

### 1. 修正题目扫描规则（已完成）

问题：`.gitignore` 已经忽略 `problem-analysis-workspace/`，但 `lib/problem.js` 的 `scanProblems()` 仍会递归扫描 `problems/**/*.md`。

任务：

- [x] 让 `lib/problem.js` 跳过 `problem-analysis-workspace/`。
- [x] 跳过 `duipai-failed/`。
- [x] 只把正式题解 `index.md` 收入题库索引。
- [x] 更新 `scripts/generate-problems-json.js` 后跑一次检查。

价值：避免过程文档、对拍记录、临时调试材料被网站误收录。

### 2. 增加题目目录一致性检查器（已完成）

建议脚本：

```bash
scripts/problem-analysis-tools/check_problem.py problems/luogu/P1001
```

检查项：

- [x] 是否存在 `index.md`。
- [x] 是否存在 `main.cpp`。
- [x] frontmatter 是否包含 `oj`、`problem_id`、`title`、`date`、`toc`、`tags`、`categories`、`source`。
- [x] `@include-code(./main.cpp, cpp)` 是否能找到文件。
- [x] 是否有不应该提交的 `problem-analysis-workspace/` 或 `duipai-failed/`。
- [x] 是否有旧结构残留，例如只存在 `1.cpp` 但没有 `main.cpp`。
- [x] 输出清晰的修复建议。

价值：写完题后能快速确认题目目录不会破坏网站渲染和题库索引。

### 3. 新建统一题目创建命令（已完成）

建议命令：

```bash
new-problem luogu P1001
```

生成结构：

```text
problems/luogu/P1001/
├── index.md
├── main.cpp
├── brute.cpp
├── gen.py
└── problem-analysis-workspace/
```

任务：

- [x] 按 `oj-problem-format-spec` 生成 `index.md` 骨架。
- [x] 生成空的 `main.cpp`。
- [x] 可选生成 `brute.cpp` 和 `gen.py`。
- [x] 不覆盖已有文件。
- [x] 支持从当前目录推断 `oj/problem_id`。

价值：减少每次开新题的重复操作，强制新题进入统一结构。

## P1：提升验证效率

### 4. 增加样例运行器（已完成）

建议命令：

```bash
check_sample.py problems/luogu/P1001
```

功能：

- [x] 自动编译 `main.cpp`。
- [x] 自动识别 `in1/out1`、`in2/out2`。
- [x] 自动识别 `data/*.in` 与 `data/*.out` 或 `data/*.ans`。
- [x] 逐组运行并 diff。
- [x] 失败时显示输入、期望输出、实际输出。

补充约定：

- [x] 无参数时在当前目录查找样例数据。
- [x] 命令名使用 `check_sample.py`，不使用 `run-samples`。
- [x] 没有答案文件时运行程序并标记为 `NO_ANSWER`。
- [x] 编译产物放在临时目录，不污染题目目录。

价值：比手动 `b 1 -i in1` 更适合批量检查样例和本地数据。

### 5. 扩展随机数据生成器

当前已有：

- array
- tree
- graph
- string
- permutation

建议新增：

- [ ] weighted-tree
- [ ] connected-graph
- [ ] dag
- [ ] bipartite-graph
- [ ] grid
- [ ] intervals
- [ ] queries
- [ ] extreme cases

重点：`extreme cases` 要能生成全相同、单调、最大值、最小值、链状树、星形树、稠密图、稀疏图等典型卡点数据。

价值：让对拍和边界验证更接近真实 OJ 数据。

### 6. 完善对拍报告

当前 `duipai.py` 已能生成 `duipai-report.md`。

可增强：

- [ ] 记录编译命令。
- [ ] 记录程序运行时间。
- [ ] 记录随机种子或生成命令。
- [ ] 失败时记录 diff 摘要。
- [ ] 成功时记录测试规模和数据类型。

价值：过程文档可以真实反映“验证过什么”，避免题解里夸大正确性。

## P2：提升题解质量

### 7. 增加题解质量检查器

建议脚本：

```bash
check-analysis problems/luogu/P1001
```

检查项：

- [ ] `### 题意` 是否为空。
- [ ] `### 思路` 是否有关键观察。
- [ ] 是否体现“朴素想法 -> 瓶颈 -> 优化 -> 正解”。
- [ ] `### 复杂度` 是否存在时间复杂度和空间复杂度。
- [ ] 是否说明边界情况。
- [ ] 是否说明关键变量和 `main.cpp` 的对应关系。
- [ ] 是否存在“显然”“很容易”等跳步表达。

价值：让题解不只是能看，而是真的能帮助复盘和学习。

### 8. 增加过程文档完整性检查

检查目录：

```text
problems/<oj>/<problem_id>/problem-analysis-workspace/
```

检查文件：

- [ ] `01-problem-understanding.md`
- [ ] `02-observation-and-model.md`
- [ ] `03-solution-derivation.md`
- [ ] `04-correctness-and-edge-cases.md`
- [ ] `05-complexity-and-implementation.md`
- [ ] `06-final-index-draft.md`
- [ ] `duipai-report.md`

价值：保证 AI 或手写过程材料完整，便于长期复盘。

## P3：建立复盘系统

### 9. 增加题目学习状态字段

建议 frontmatter 增加可选字段：

```yaml
status: "learning"
difficulty:
first_solved:
last_review:
mistakes: []
patterns: []
```

字段含义：

- `status`：`learning`、`solved`、`review`、`hard`
- `difficulty`：题目难度或个人体感难度
- `first_solved`：第一次完成时间
- `last_review`：最近复盘时间
- `mistakes`：错误类型，例如 `边界`、`复杂度`、`建模`、`实现`
- `patterns`：题型模式，例如 `双指针`、`前缀和`、`树形DP`

价值：把题库从文章集合升级为训练记录。

### 10. 增加复习列表脚本

建议命令：

```bash
review-list
```

输出：

- [ ] 最近很久没复习的题。
- [ ] `status: hard` 的题。
- [ ] 同一错误类型反复出现的题。
- [ ] 某算法模式下还没掌握的题。
- [ ] 缺少题解或缺少代码的题。

价值：帮助选择下一批该复习或补强的题目。

### 11. 增加学习仪表盘

可以在网站里增加一个学习视角：

- [ ] 今天/本周写了几题。
- [ ] 哪些题有 `problem-analysis-workspace/`。
- [ ] 哪些题没有 `main.cpp`。
- [ ] 哪些题没有完整题解。
- [ ] 哪些题对拍失败过。
- [ ] 哪些题需要复习。

价值：让题库变成持续训练系统，而不是静态文档站。

## 推荐实现顺序

1. 修 `lib/problem.js` 跳过过程目录。
2. 写 `check_problem.py`。
3. 写 `new-problem` 命令。
4. 写 `check_sample.py`。
5. 做 `check-analysis`。
6. 再做学习状态字段和复盘系统。
