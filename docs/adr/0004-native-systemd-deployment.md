---
status: accepted
---

# Deploy immutable releases with SSH and systemd

生产部署把应用源码、题目内容和生产依赖分别保存。应用源码变化时上传小型不可变
app release；题目内容变化时通过 rsync 生成增量内容快照；组合 deployment 记录
三者的版本并由 systemd 直接运行。GitHub Actions 只负责代码验证，不保存 VPS
密钥，也不触发生产部署。

app 和 content 都必须通过 `git archive` 从目标 commit 导出，不能复制当前工作
目录。这样既能保证发布内容可以追溯，也能排除 `problems/` 下被 Git 忽略的分析
工作区、对拍产物和临时文件。

## Consequences

VPS 的 `/opt/problems-solution/current` 指向组合 deployment，后者分别引用 app
release 和 content snapshot。部署先在随机端口以低权限用户启动候选版本；候选
版本健康后再切换软链接并重启
`problems-solution.service`。本机端口或公网健康检查失败时，部署脚本恢复上一
组合 deployment 并重新启动服务。

内容快照使用上一快照作为 rsync `--link-dest` 基准。只有内容发生变化时才执行
rsync，网络只传新增或修改的文件；未变化文件通过硬链接复用。app release 不包含
题目内容，且仅在非内容路径发生变化时上传。

生产依赖按 `package-lock.json` 哈希、操作系统、CPU 架构和构建时 Node ABI
缓存。纯 JavaScript 依赖允许部署到不同 ABI 的受支持 Node.js；检测到原生
`.node` 模块时要求 VPS 的 Node ABI 一致。只有缓存不存在时才上传依赖包。服务器
不需要访问 GitHub，也不需要 GitHub Deploy Key 或 GHCR Token。

所有发布都通过重启服务激活，包括只修改 `problems/` 或 `problem-sets/` 的提交。
这取代 ADR 0002 中依赖 Docker bind mount 和运行中 Git worktree 的部署方式。
应用仍保留 `SIGHUP` 内容刷新能力，但原生发布流程不依赖它。

首次迁移允许脚本检测、停止并在失败时恢复旧的 `problems-solution` 容器。原生
服务通过全部检查后删除旧容器；后续部署路径不需要 Docker。
