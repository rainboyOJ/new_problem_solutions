import test from "node:test";
import assert from "node:assert/strict";

import { ApiClient } from "../src/client/apiClient.js";

function createResponse(status, jsonData) {
  return {
    ok: status >= 200 && status < 300,
    status,
    async json() {
      return jsonData;
    }
  };
}

test("ApiClient searchProblems maps query to search", async () => {
  let calledUrl;
  const client = new ApiClient({
    baseUrl: "http://127.0.0.1:3000",
    fetchImpl: async (url) => {
      calledUrl = url;
      return createResponse(200, { data: [] });
    }
  });

  await client.searchProblems({ query: "dp", oj: "poj", tag: "graph", page: 2, limit: 50 });

  const parsed = new URL(calledUrl);
  assert.equal(parsed.pathname, "/api/problems");
  assert.equal(parsed.searchParams.get("search"), "dp");
  assert.equal(parsed.searchParams.get("oj"), "poj");
  assert.equal(parsed.searchParams.get("tag"), "graph");
  assert.equal(parsed.searchParams.get("page"), "2");
  assert.equal(parsed.searchParams.get("limit"), "50");
});

test("ApiClient getProblemDetail builds expected path", async () => {
  let calledUrl;
  const client = new ApiClient({
    baseUrl: "http://127.0.0.1:3000",
    fetchImpl: async (url) => {
      calledUrl = url;
      return createResponse(200, { oj: "poj", problem_id: "3061" });
    }
  });

  await client.getProblemDetail({ oj: "poj", id: "3061" });

  const parsed = new URL(calledUrl);
  assert.equal(parsed.pathname, "/api/problems/poj/3061");
});

test("ApiClient maps 404 to NOT_FOUND", async () => {
  const client = new ApiClient({
    baseUrl: "http://127.0.0.1:3000",
    fetchImpl: async () => createResponse(404, { error: "not found" })
  });

  await assert.rejects(() => client.getProblemDetail({ oj: "poj", id: "x" }), (error) => {
    assert.equal(error.code, "NOT_FOUND");
    return true;
  });
});

test("ApiClient maps upstream 503 to UPSTREAM_ERROR", async () => {
  const client = new ApiClient({
    baseUrl: "http://127.0.0.1:3000",
    fetchImpl: async () => createResponse(503, { error: "service unavailable" })
  });

  await assert.rejects(() => client.searchProblems({}), (error) => {
    assert.equal(error.code, "UPSTREAM_ERROR");
    return true;
  });
});

test("ApiClient maps network failure to UPSTREAM_UNAVAILABLE", async () => {
  const client = new ApiClient({
    baseUrl: "http://127.0.0.1:3000",
    fetchImpl: async () => {
      throw new TypeError("fetch failed");
    }
  });

  await assert.rejects(() => client.searchProblems({}), (error) => {
    assert.equal(error.code, "UPSTREAM_UNAVAILABLE");
    return true;
  });
});
