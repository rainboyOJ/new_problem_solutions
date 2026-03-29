import test from "node:test";
import assert from "node:assert/strict";

import { GET_PROBLEM_DETAIL_ZOD_SCHEMA, createGetProblemDetailHandler } from "../src/tools/getProblemDetail.js";

test("get_problem_detail validates required fields", async () => {
  const handler = createGetProblemDetailHandler({
    apiClient: {
      async getProblemDetail() {
        return {};
      }
    }
  });

  await assert.rejects(() => handler({ id: "1000" }), (error) => {
    assert.equal(error.code, "BAD_REQUEST");
    return true;
  });
});

test("get_problem_detail normalizes output", async () => {
  const handler = createGetProblemDetailHandler({
    apiClient: {
      async getProblemDetail() {
        return {
          oj: "poj",
          problem_id: "3061",
          title: "Subsequence",
          tags: ["two-pointers"],
          url: "https://example.com/3061",
          md_path: "poj/3061.md",
          html_content: "<p>body</p>",
          md_content: "# Subsequence"
        };
      }
    }
  });

  const result = await handler({ oj: "poj", id: "3061" });

  assert.deepEqual(result, {
    oj: "poj",
    problem_id: "3061",
    title: "Subsequence",
    tags: ["two-pointers"],
    url: "https://example.com/3061",
    md_content: "# Subsequence",
    html_content: "<p>body</p>"
  });
});

test("get_problem_detail zod schema rejects unknown fields", () => {
  const parsed = GET_PROBLEM_DETAIL_ZOD_SCHEMA.safeParse({ oj: "poj", id: "1", extra: "x" });
  assert.equal(parsed.success, false);
});
