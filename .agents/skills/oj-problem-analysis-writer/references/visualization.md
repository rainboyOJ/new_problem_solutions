# 可视化评估与产物

图示服务于理解。先按 [读者与讲解规范](reader-and-explanation.md) 区分必须图解的图论定理、关键结构结论与其他按需评估的内容；不能把前者降为可选装饰。`02-observation-and-model.md` 必须记录图示对应的推理步骤、推荐形式，以及其他内容使用或不使用图示的理由。

长证明优先在同一张 SVG、Mermaid 或 Graphviz 图上分步说明，保持节点名和标记一致；不同小步可以复用同一张图，不要求每段新画一张。展示关键结构的局部图不能被只有流程箭头的总览图代替。

优先考虑：图论用 Graphviz/Mermaid 样例图；树、二叉树、线段树用 `tree_draw.py` SVG；DP 必须在对应思路放小规模 DP/状态转移表（说明行列、单元格、至少一轮转移前后）；网格用二维表；搜索/递归用搜索树或状态图；复杂模拟用步骤表。若有用，调用 `oj-sample-visualizer`，让它生成题目专用 `problem-analysis-workspace/viz_render.py` 和素材；正文只引用产物，不粘贴脚本。

非平凡算法题可以生成 `final-visualization.md`，把简洁的 `## 图示解析` 接在 `## 总结` 后。默认用 ASCII，只有交叉边、多重汇合或 ASCII 不清楚时才用 Mermaid；图示只展示模型、关键观察、算法和答案路线，不重复代码、完整 DP 或证明。直接输入输出、极短模拟和纯语言学习文章可以省略，但要记录理由。

每个图/表前用一句话说明展示内容，后用 2--5 句解释读者应观察什么；数据保持小且与样例或关键局部相关。普通题解通常 1--2 个可视化块，难题最多 3 个；超过 30 个节点、`10 x 10` DP 表或搜索树 3 层时只展示关键局部。图表格式、放置位置和 Markdown 语法以 `oj-problem-format-spec` 与 `rbook-markdown` 为准。

生成树图时可使用：

```bash
ptool --cd problems/<oj>/<problem_id> tree_draw --type binary --input tree.txt --output tree.svg --markdown
ptool --cd problems/<oj>/<problem_id> tree_draw --type segment --size 8 --output segment-tree.svg --markdown
```

在文章中用 `![说明](./tree.svg)` 等标准相对路径引用。
