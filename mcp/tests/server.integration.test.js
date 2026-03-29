import test from "node:test";
import assert from "node:assert/strict";
import http from "node:http";
import { Client } from "@modelcontextprotocol/sdk/client/index.js";
import { StreamableHTTPClientTransport } from "@modelcontextprotocol/sdk/client/streamableHttp.js";

import { createGatewayServer } from "../src/server.js";

function createUpstreamServer() {
  const server = http.createServer((req, res) => {
    const url = new URL(req.url, "http://127.0.0.1");

    if (req.method === "GET" && url.pathname === "/api/problems") {
      const data = {
        data: [
          {
            oj: "poj",
            problem_id: "3061",
            title: "Subsequence",
            tags: ["two-pointers"],
            url: "https://example.com/3061"
          }
        ],
        pagination: {
          total: 1,
          page: Number(url.searchParams.get("page") || 1),
          limit: Number(url.searchParams.get("limit") || 20),
          totalPages: 1
        }
      };
      res.writeHead(200, { "content-type": "application/json" });
      res.end(JSON.stringify(data));
      return;
    }

    if (req.method === "GET" && url.pathname === "/api/problems/poj/3061") {
      const data = {
        oj: "poj",
        problem_id: "3061",
        title: "Subsequence",
        tags: ["two-pointers"],
        url: "https://example.com/3061",
        md_path: "poj/3061.md",
        html_content: "<p>body</p>",
        md_content: "# Subsequence"
      };
      res.writeHead(200, { "content-type": "application/json" });
      res.end(JSON.stringify(data));
      return;
    }

    res.writeHead(404, { "content-type": "application/json" });
    res.end(JSON.stringify({ error: "not found" }));
  });

  return server;
}

async function listen(server) {
  await new Promise((resolve) => server.listen(0, "127.0.0.1", resolve));
  return server.address().port;
}

async function closeServer(server) {
  await new Promise((resolve, reject) => {
    server.close((error) => {
      if (error) {
        reject(error);
        return;
      }
      resolve();
    });
  });
}

function createLoggerCapture() {
  const logs = {
    info: [],
    warn: [],
    error: []
  };

  return {
    logs,
    logger: {
      info(entry) {
        logs.info.push(entry);
      },
      warn(entry) {
        logs.warn.push(entry);
      },
      error(entry) {
        logs.error.push(entry);
      }
    }
  };
}

async function createMcpClient(baseUrl) {
  const client = new Client({ name: "test-client", version: "1.0.0" });
  const transport = new StreamableHTTPClientTransport(new URL(`${baseUrl}/mcp`));
  await client.connect(transport);
  return { client, transport };
}

test("gateway serves JSON tool endpoints", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);
  const { logs, logger } = createLoggerCapture();

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    enableMcpRegistration: false,
    logger
  });

  await gateway.start();

  try {
    const baseUrl = gateway.baseUrl;
    const searchResponse = await fetch(`${baseUrl}/tools/search_problems`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({ query: "subsequence" })
    });
    assert.equal(searchResponse.status, 200);
    const searchBody = await searchResponse.json();
    assert.equal(searchBody.ok, true);
    assert.deepEqual(searchBody.result, {
      items: [
        {
          oj: "poj",
          problem_id: "3061",
          title: "Subsequence",
          tags: ["two-pointers"],
          url: "https://example.com/3061"
        }
      ],
      pagination: {
        total: 1,
        page: 1,
        limit: 20,
        totalPages: 1
      }
    });

    const detailResponse = await fetch(`${baseUrl}/tools/get_problem_detail`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({ oj: "poj", id: "3061" })
    });
    assert.equal(detailResponse.status, 200);
    const detailBody = await detailResponse.json();
    assert.equal(detailBody.ok, true);
    assert.deepEqual(detailBody.result, {
      oj: "poj",
      problem_id: "3061",
      title: "Subsequence",
      tags: ["two-pointers"],
      url: "https://example.com/3061",
      md_content: "# Subsequence",
      html_content: "<p>body</p>"
    });

    assert.equal(logs.info.length >= 2, true);
    const parsed = JSON.parse(logs.info[0]);
    assert.equal(typeof parsed.trace_id, "string");
    assert.equal(parsed.tool, "search_problems");
    assert.equal(parsed.upstream, "/api/problems");
    assert.equal(parsed.status, 200);
    assert.equal(typeof parsed.latency_ms, "number");
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("gateway exposes /tools/list with input schemas", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    enableMcpRegistration: false
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/tools/list`);
    assert.equal(response.status, 200);
    const body = await response.json();
    assert.equal(Array.isArray(body.tools), true);
    const searchTool = body.tools.find((tool) => tool.name === "search_problems");
    assert.equal(Boolean(searchTool), true);
    assert.equal(searchTool.inputSchema.type, "object");
    assert.equal(Boolean(searchTool.inputSchema.properties.query), true);
    assert.equal(Boolean(searchTool.inputSchema.properties.limit), true);
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("gateway /rpc executes tool and returns raw tool output", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    enableMcpRegistration: false
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/rpc`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({ tool: "search_problems", input: { query: "subsequence" } })
    });

    assert.equal(response.status, 200);
    const body = await response.json();
    assert.equal(Array.isArray(body.items), true);
    assert.equal(Boolean(body.ok), false);
    assert.equal(body.items[0].problem_id, "3061");
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("gateway /rpc supports arguments compatibility field", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    enableMcpRegistration: false
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/rpc`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({ tool: "search_problems", arguments: { query: "subsequence", page: 2 } })
    });

    assert.equal(response.status, 200);
    const body = await response.json();
    assert.equal(Array.isArray(body.items), true);
    assert.equal(body.items[0].problem_id, "3061");
    assert.equal(body.pagination.page, 2);
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("gateway /rpc errors use normalized shape", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    enableMcpRegistration: false
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/rpc`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({ tool: "get_problem_detail", input: { oj: "poj" } })
    });

    assert.equal(response.status, 400);
    const body = await response.json();
    assert.equal(body.ok, false);
    assert.equal(body.error.code, "BAD_REQUEST");
    assert.equal(typeof body.error.trace_id, "string");
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("gateway supports SSE-style responses", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    enableMcpRegistration: false
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/tools/search_problems?sse=1`, {
      method: "POST",
      headers: { "content-type": "application/json", accept: "text/event-stream" },
      body: JSON.stringify({ query: "subsequence" })
    });

    assert.equal(response.status, 200);
    const contentType = response.headers.get("content-type") || "";
    assert.match(contentType, /text\/event-stream/);

    const body = await response.text();
    assert.match(body, /event: result/);
    assert.match(body, /"ok":true/);
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("gateway errors include deterministic code and trace_id", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);
  const { logs, logger } = createLoggerCapture();

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    enableMcpRegistration: false,
    logger
  });

  await gateway.start();

  try {
    const badInputResponse = await fetch(`${gateway.baseUrl}/tools/search_problems`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({ limit: 1000 })
    });

    assert.equal(badInputResponse.status, 400);
    const badInputBody = await badInputResponse.json();
    assert.equal(badInputBody.ok, false);
    assert.equal(badInputBody.error.code, "BAD_REQUEST");
    assert.equal(typeof badInputBody.error.trace_id, "string");
    assert.equal(logs.warn.length, 1);
    assert.equal(logs.error.length, 0);
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("gateway exposes MCP protocol endpoint", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    }
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/mcp`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({
        jsonrpc: "2.0",
        id: 1,
        method: "tools/list",
        params: {}
      })
    });

    assert.notEqual(response.status, 404);
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("/mcp auth failure returns 401", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: "secret-token"
    }
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/mcp`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({
        jsonrpc: "2.0",
        id: 1,
        method: "tools/list",
        params: {}
      })
    });

    assert.equal(response.status, 401);
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("/mcp invalid initialize payload returns 400", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    }
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/mcp`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({
        jsonrpc: "2.0",
        id: 1,
        method: "tools/list",
        params: {}
      })
    });

    assert.equal(response.status, 400);
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("gateway logs INTERNAL_ERROR with error level", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);
  const { logs, logger } = createLoggerCapture();

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    apiClient: {
      async searchProblems() {
        throw new Error("unexpected boom");
      },
      async getProblemDetail() {
        return {};
      }
    },
    enableMcpRegistration: false,
    logger
  });

  await gateway.start();

  try {
    const response = await fetch(`${gateway.baseUrl}/tools/search_problems`, {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({ query: "x" })
    });
    assert.equal(response.status, 500);
    const body = await response.json();
    assert.equal(body.error.code, "INTERNAL_ERROR");
    assert.equal(logs.error.length, 1);
    assert.equal(logs.warn.length, 0);
  } finally {
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("MCP tool invocation logs success entry", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);
  const { logs, logger } = createLoggerCapture();

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    logger
  });

  await gateway.start();

  let client;
  let transport;
  try {
    ({ client, transport } = await createMcpClient(gateway.baseUrl));
    const result = await client.callTool({
      name: "search_problems",
      arguments: { query: "subsequence" }
    });

    assert.equal(result.isError, undefined);
    assert.equal(logs.info.length >= 1, true);
    const parsed = JSON.parse(logs.info[0]);
    assert.equal(parsed.tool, "search_problems");
    assert.equal(parsed.upstream, "/api/problems");
    assert.equal(parsed.status, 200);
    assert.equal(typeof parsed.trace_id, "string");
  } finally {
    if (client) {
      await client.close();
    }
    if (transport) {
      await transport.close();
    }
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("MCP tools/list includes input schema properties", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    }
  });

  await gateway.start();

  let client;
  let transport;
  try {
    ({ client, transport } = await createMcpClient(gateway.baseUrl));
    const listed = await client.listTools();
    const searchTool = listed.tools.find((tool) => tool.name === "search_problems");
    assert.equal(Boolean(searchTool), true);
    assert.equal(searchTool.inputSchema.type, "object");
    assert.equal(Boolean(searchTool.inputSchema.properties.query), true);
    assert.equal(Boolean(searchTool.inputSchema.properties.limit), true);
  } finally {
    if (client) {
      await client.close();
    }
    if (transport) {
      await transport.close();
    }
    await gateway.stop();
    await closeServer(upstream);
  }
});

test("MCP tool errors include machine-readable normalized payload", async () => {
  const upstream = createUpstreamServer();
  const upstreamPort = await listen(upstream);
  const { logs, logger } = createLoggerCapture();

  const gateway = createGatewayServer({
    config: {
      mcpHost: "127.0.0.1",
      mcpPort: 0,
      targetApiBaseUrl: `http://127.0.0.1:${upstreamPort}`,
      upstreamTimeoutMs: 5000,
      mcpAuthToken: undefined
    },
    logger
  });

  await gateway.start();

  let client;
  let transport;
  try {
    ({ client, transport } = await createMcpClient(gateway.baseUrl));
    const result = await client.callTool({
      name: "get_problem_detail",
      arguments: { oj: "poj", id: "does-not-exist" }
    });

    assert.equal(result.isError, true);
    const payload = JSON.parse(result.content[0].text);
    assert.equal(payload.error.code, "NOT_FOUND");
    assert.equal(typeof payload.error.trace_id, "string");
    assert.equal(logs.warn.length >= 1, true);
    const parsed = JSON.parse(logs.warn[0]);
    assert.equal(parsed.tool, "get_problem_detail");
    assert.equal(parsed.status, 404);
  } finally {
    if (client) {
      await client.close();
    }
    if (transport) {
      await transport.close();
    }
    await gateway.stop();
    await closeServer(upstream);
  }
});
