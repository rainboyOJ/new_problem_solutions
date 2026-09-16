---
description: 批量整理题目 AI 对话文档，补全元数据并按日期与 slug 重命名
---
目标目录：优先使用用户消息里指定的 `talking_with_ai/` 路径；没给路径时，只从当前 `talking_with_ai/` 或当前题目目录下唯一的 `talking_with_ai/` 定位。不能唯一定位就请求路径，不扫描全仓库。

完整读取并遵循 `.agents/skills/rbook-ai-note-organizer/SKILL.md`。对目标目录第一层每份非隐藏的普通 `.md` 执行预检和整理，包括已有元数据或 `draft: true` 的文档；不处理子目录、隐藏文件或符号链接。

预检后直接处理安全的文件：保留合法元数据和其他 frontmatter 字段，缺少 `draft` 时写 `false`；依据对话内容补齐缺失或无效信息，统一命名为 `YYYY-MM-DD--slug.md`，并修复同目录明确指向旧文件名的相对链接。日期或主题无法确认、slug 或文件名冲突无法解决时跳过该文件并报告；不覆盖文件，不改写对话正文，不修改目录外引用。

完成后按 skill 验证并报告逐文件改名、元数据变更、跳过项和验证结果；不要自动 commit 或 push。
