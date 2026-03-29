import test from "node:test";
import assert from "node:assert/strict";

import { SEARCH_PROBLEMS_ZOD_SCHEMA, createSearchProblemsHandler } from "../src/tools/searchProblems.js";

test("search_problems uses default limit and normalizes output", async () => {
  let received;
  const handler = createSearchProblemsHandler({
    apiClient: {
      async searchProblems(input) {
        received = input;
        return {
          data: [
            {
              oj: "poj",
              problem_id: "3061",
              title: "Subsequence",
              tags: ["two-pointers"],
              url: "https://example.com/3061",
              source: "rbook"
            }
          ],
          pagination: {
            total: 1,
            page: 1,
            limit: 20,
            totalPages: 1
          }
        };
      }
    }
  });

  const result = await handler({ query: "subsequence" });

  assert.equal(received.limit, 20);
  assert.deepEqual(result, {
    items: [
      {
        oj: "poj",
        problem_id: "3061",
        title: "Subsequence",
        tags: ["two-pointers"],
        url: "https://example.com/3061",
        source: "rbook"
      }
    ],
    pagination: {
      total: 1,
      page: 1,
      limit: 20,
      totalPages: 1
    }
  });
});

test("search_problems enforces max limit", async () => {
  const handler = createSearchProblemsHandler({
    apiClient: {
      async searchProblems() {
        return { data: [], pagination: { total: 0, page: 1, limit: 100, totalPages: 0 } };
      }
    }
  });

  await assert.rejects(() => handler({ limit: 101 }), (error) => {
    assert.equal(error.code, "BAD_REQUEST");
    return true;
  });
});

test("search_problems zod schema rejects unknown fields", () => {
  const parsed = SEARCH_PROBLEMS_ZOD_SCHEMA.safeParse({ query: "x", unknown: true });
  assert.equal(parsed.success, false);
});
