---
name: project-pre-push-check
description: Run and diagnose this repository's complete pre-push verification. Use this skill whenever the user asks to check whether the project can run, verify before push, diagnose a pre-push hook failure, 检查项目, push 前检查, or determine why GitHub verification blocked deployment. It checks the exact Git state, then uses the repository's canonical verification command; it does not modify files unless the user explicitly requests a fix.
---

# 项目 Push 前检查

本 skill 用于确认当前仓库是否满足 push 和部署条件，并定位失败原因。检查逻辑以仓库脚本为唯一事实来源，不在 skill 中复制测试、构建或健康检查实现。

默认只检查和诊断。除非用户明确要求“修复”“修改”或“解决错误”，否则不要编辑文件、安装依赖、提交或 push。

## 执行流程

1. 进入仓库根目录。
2. 运行下面的命令检查 Git 状态：

   ```bash
   git status --porcelain=v1 --untracked-files=all
   ```

3. 如果有输出，停止检查并报告 Git 前置条件失败。列出脏文件，说明 push hook 要求工作区完全干净；不要擅自提交、删除或忽略文件。
4. 如果工作区干净，运行唯一的完整检查入口：

   ```bash
   npm run verify:push
   ```

5. 保留命令的原始错误，重点读取最后的 `[verify:push] 检查失败` 摘要。
6. 用中文报告结果，不要只说“命令失败”。

## 检查范围

`npm run verify:push` 依次检查：

- Node.js 版本、lockfile 和本地依赖状态。
- `npm test` 全部自动化测试。
- 在临时目录编译关系图，并与 `public/relations-graph/` 比较。
- 扫描全部题目和题目单 frontmatter，要求内容状态为 `healthy`。
- 临时启动真实 Fastify 服务，验证 `/api/health/live` 和 `/api/health/content`。

不要根据改动路径省略阶段，也不要用单独运行某一阶段的成功代替完整检查。

## 失败诊断

按失败阶段给出针对性结论：

- `运行环境与依赖`：报告当前 Node 版本或依赖错误。依赖缺失时建议用户手动执行 `npm ci`，不要自动执行。
- `自动化测试`：指出第一个失败测试、断言差异和相关文件。
- `关系图编译与产物一致性`：区分编译错误与已提交产物过期。产物过期时建议运行 `npm run build` 并检查生成文件。
- `全量内容索引`：列出无效题目或题目单路径及 frontmatter 错误。
- `真实服务启动与健康检查`：引用服务日志中的根因，并说明失败的是启动、存活检查还是内容健康检查。

不要把警告误报成失败。以命令退出码和统一摘要为准。

## 报告格式

成功时使用：

```text
检查结果：通过
检查范围：依赖、测试、构建产物、全量内容索引、真实服务健康
结论：当前版本满足 push 条件
```

失败时使用：

```text
检查结果：失败
失败阶段：<阶段>
失败命令：<命令>
关键原因：<从原始日志提炼的具体原因>
建议动作：<最小且明确的下一步>
```

## 修复模式

只有用户明确要求修复时才修改文件。修复后必须重新运行完整的 `npm run verify:push`，不能只重跑原先失败的子命令。未经用户明确要求，不要 commit 或 push。
