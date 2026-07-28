from __future__ import annotations

from html import unescape
import json
import re
from typing import Any

from .base import BaseFetcher, FetchError, FetchResult, ProblemData


LEETCODECN_ORIGIN = "https://leetcode.cn"
QUESTION_QUERY = """
query questionData($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    questionFrontendId
    translatedTitle
    translatedContent
    titleSlug
    difficulty
    exampleTestcases
    metaData
    codeSnippets {
      lang
      langSlug
      code
    }
  }
}
""".strip()


def strip_html_tags(value: str) -> str:
    text = re.sub(r"<br\s*/?>", "\n", value, flags=re.I)
    text = re.sub(r"<[^>]+>", "", text)
    return unescape(text).replace("\xa0", " ").strip()


def html_to_markdown(value: str) -> str:
    """Convert the subset of HTML used by LeetCode statements to Markdown."""

    text = value.replace("\r\n", "\n").replace("\r", "\n")
    code_blocks: list[str] = []

    def replace_pre(match: re.Match[str]) -> str:
        code = strip_html_tags(match.group(1)).strip("\n")
        marker = f"@@LEETCODE_PRE_{len(code_blocks)}@@"
        code_blocks.append(f"```text\n{code}\n```")
        return f"\n\n{marker}\n\n"

    text = re.sub(r"<pre\b[^>]*>([\s\S]*?)</pre>", replace_pre, text, flags=re.I)
    text = re.sub(
        r"<a\b[^>]*href=[\"']([^\"']+)[\"'][^>]*>([\s\S]*?)</a>",
        lambda match: f"[{strip_html_tags(match.group(2))}]({unescape(match.group(1))})",
        text,
        flags=re.I,
    )
    text = re.sub(
        r"<sup\b[^>]*>([\s\S]*?)</sup>",
        lambda match: "^" + strip_html_tags(match.group(1)),
        text,
        flags=re.I,
    )
    text = re.sub(
        r"<code\b[^>]*>([\s\S]*?)</code>",
        lambda match: f"`{strip_html_tags(match.group(1))}`",
        text,
        flags=re.I,
    )
    text = re.sub(
        r"<(strong|b)\b[^>]*>([\s\S]*?)</\1>",
        lambda match: f"**{strip_html_tags(match.group(2))}**",
        text,
        flags=re.I,
    )
    text = re.sub(
        r"<(em|i)\b[^>]*>([\s\S]*?)</\1>",
        lambda match: f"*{strip_html_tags(match.group(2))}*",
        text,
        flags=re.I,
    )
    # Adjacent bold and italic fragments otherwise merge into an accidental *** run.
    text = re.sub(r"\*\*\*(?=`)", "** *", text)
    text = re.sub(r"<li\b[^>]*>", "\n- ", text, flags=re.I)
    text = re.sub(r"</li>", "", text, flags=re.I)
    text = re.sub(r"<br\s*/?>", "\n", text, flags=re.I)
    text = re.sub(r"</(p|div|ul|ol|section|h[1-6])>", "\n\n", text, flags=re.I)
    text = re.sub(r"<(p|div|ul|ol|section|h[1-6])\b[^>]*>", "", text, flags=re.I)
    text = re.sub(r"<[^>]+>", "", text)
    text = unescape(text).replace("\xa0", " ")

    lines = [re.sub(r"[ \t]+$", "", line) for line in text.splitlines()]
    normalized = "\n".join(lines)
    normalized = re.sub(r"\n{3,}", "\n\n", normalized).strip()
    for index, block in enumerate(code_blocks):
        normalized = normalized.replace(f"@@LEETCODE_PRE_{index}@@", block)
    return normalized.strip()


class LeetCodeCNFetcher(BaseFetcher):
    name = "leetcodecn"
    aliases = ("leetcode", "leetcode-cn", "lc")
    site_prefixes = (
        "https://leetcode.cn/problems/",
        "http://leetcode.cn/problems/",
        "https://www.leetcode.cn/problems/",
        "http://www.leetcode.cn/problems/",
    )

    def parse_url(self, url: str) -> tuple[str, str]:
        clean = url.split("?")[0].split("#")[0]
        match = re.search(r"/problems/([^/]+)(?:/(?:description)?)?/?$", clean)
        if not match:
            raise FetchError(f"无法从 LeetCodeCN URL 解析题目 slug：{url}")
        return self.name, match.group(1)

    def problem_link(self, title_slug: str) -> str:
        return f"{LEETCODECN_ORIGIN}/problems/{title_slug}/"

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        raw_id = str(problem_id).strip()
        title_slug = self.slug_from_composite_id(raw_id)
        source = self.problem_link(title_slug) if title_slug else f"{LEETCODECN_ORIGIN}/problemset/"
        directory_id = title_slug or raw_id.replace(" ", "_")
        return ProblemData(
            oj=self.name,
            problem_id=directory_id,
            problem_dir_id=directory_id,
            source=source,
            title=raw_id,
        )

    def slug_from_composite_id(self, problem_id: str) -> str:
        match = re.fullmatch(r"[^.]+\.([A-Za-z0-9_-]+)", problem_id)
        if match:
            return match.group(1)
        # 纯数字仍然表示 LeetCode 题号；带字母或连字符的值可直接视为 slug，
        # 例如 3sum、0-1-matrix，避免再次请求全量题目列表。
        if re.fullmatch(r"(?=.*[A-Za-z_-])[A-Za-z0-9][A-Za-z0-9_-]*", problem_id):
            return problem_id
        return ""

    def resolve_slug(self, problem_id: str) -> str:
        composite_slug = self.slug_from_composite_id(problem_id)
        if composite_slug:
            return composite_slug

        payload_text = self.http_get(f"{LEETCODECN_ORIGIN}/api/problems/all/")
        try:
            payload = json.loads(payload_text)
        except json.JSONDecodeError as exc:
            raise FetchError(f"LeetCodeCN 题目列表不是有效 JSON：{exc}") from exc
        pairs = payload.get("stat_status_pairs") if isinstance(payload, dict) else None
        if not isinstance(pairs, list):
            raise FetchError("LeetCodeCN 题目列表缺少 stat_status_pairs。")

        expected = str(problem_id).strip()
        for item in pairs:
            stat = item.get("stat") if isinstance(item, dict) else None
            if not isinstance(stat, dict):
                continue
            if str(stat.get("frontend_question_id", "")).strip() == expected:
                title_slug = stat.get("question__title_slug")
                if isinstance(title_slug, str) and title_slug:
                    return title_slug
        raise FetchError(f"LeetCodeCN 未找到题号：{problem_id}")

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        title_slug = self.resolve_slug(str(problem_id).strip())
        payload = self.http_post_json(
            f"{LEETCODECN_ORIGIN}/graphql/",
            {
                "operationName": "questionData",
                "variables": {"titleSlug": title_slug},
                "query": QUESTION_QUERY,
            },
            headers={
                "Origin": LEETCODECN_ORIGIN,
                "Referer": self.problem_link(title_slug),
            },
        )
        data = self.parse_payload(payload, title_slug)
        return FetchResult(data=data, fetched=True, warnings=list(data.warnings))

    def fetch_by_url(self, url: str) -> FetchResult:
        oj, title_slug = self.parse_url(url)
        return self.fetch(oj, title_slug)

    def parse_payload(self, payload: dict[str, Any], requested_slug: str) -> ProblemData:
        errors = payload.get("errors")
        if isinstance(errors, list) and errors:
            message = errors[0].get("message") if isinstance(errors[0], dict) else str(errors[0])
            raise FetchError(f"LeetCodeCN GraphQL 返回错误：{message}")

        root = payload.get("data")
        question = root.get("question") if isinstance(root, dict) else None
        if not isinstance(question, dict):
            raise FetchError(f"LeetCodeCN 未返回题目数据：{requested_slug}")

        frontend_id = question.get("questionFrontendId")
        title_slug = question.get("titleSlug")
        title = question.get("translatedTitle")
        content = question.get("translatedContent")
        if not isinstance(frontend_id, str) or not frontend_id.strip():
            raise FetchError("LeetCodeCN 题目缺少 questionFrontendId。")
        if not isinstance(title_slug, str) or not title_slug.strip():
            raise FetchError("LeetCodeCN 题目缺少 titleSlug。")
        if not isinstance(title, str) or not title.strip():
            raise FetchError("LeetCodeCN 题目缺少中文标题。")
        if not isinstance(content, str) or not content.strip():
            raise FetchError("LeetCodeCN 题目缺少中文题面。")

        body = html_to_markdown(content)
        statement = f"# {frontend_id.strip()} {title.strip()}\n\n## 题目描述\n\n{body}\n"
        warning = "LeetCodeCN 使用函数签名提交；示例保留在 problem.md 中，不生成传统 in/out 样例文件。"
        return ProblemData(
            oj=self.name,
            problem_id=title_slug.strip(),
            problem_dir_id=title_slug.strip(),
            source=self.problem_link(title_slug.strip()),
            title=title.strip(),
            statement_md=statement,
            samples=[],
            warnings=[warning],
        )
