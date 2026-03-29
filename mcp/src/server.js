import http from "node:http";
import { randomUUID } from "node:crypto";

import { isInitializeRequest } from "@modelcontextprotocol/sdk/types.js";
import { McpServer } from "@modelcontextprotocol/sdk/server/mcp.js";
import { StreamableHTTPServerTransport } from "@modelcontextprotocol/sdk/server/streamableHttp.js";

import { loadConfig } from "./config.js";
import { ApiClient } from "./client/apiClient.js";
import { AppError, ERROR_CODES, normalizeError } from "./errors.js";
import {
  SEARCH_PROBLEMS_TOOL,
  SEARCH_PROBLEMS_ZOD_SCHEMA,
  createSearchProblemsHandler
} from "./tools/searchProblems.js";
import {
  GET_PROBLEM_DETAIL_TOOL,
  GET_PROBLEM_DETAIL_ZOD_SCHEMA,
  createGetProblemDetailHandler
} from "./tools/getProblemDetail.js";

const TOOL_UPSTREAM_PATH = {
  search_problems: "/api/problems",
  get_problem_detail: "/api/problems/:oj/:id"
};

function createTraceId() {
  return randomUUID();
}

function resolveLogMethod(logger, level) {
  if (typeof logger?.[level] === "function") {
    return logger[level].bind(logger);
  }
  if (typeof logger?.log === "function") {
    return logger.log.bind(logger);
  }
  return () => {};
}

function getErrorLogLevel(code) {
  if (code === ERROR_CODES.INTERNAL_ERROR) {
    return "error";
  }
  return "warn";
}

function normalizeErrorCode(code) {
  if (Object.values(ERROR_CODES).includes(code)) {
    return code;
  }
  return ERROR_CODES.INTERNAL_ERROR;
}

function isSseRequest(req, parsedUrl) {
  const accept = req.headers.accept || "";
  return parsedUrl.searchParams.get("sse") === "1" || accept.includes("text/event-stream");
}

function sendJson(res, status, body) {
  res.writeHead(status, {
    "content-type": "application/json; charset=utf-8"
  });
  res.end(JSON.stringify(body));
}

function sendSse(res, status, body) {
  res.writeHead(status, {
    "content-type": "text/event-stream; charset=utf-8",
    "cache-control": "no-cache",
    connection: "keep-alive"
  });
  res.write("event: result\n");
  res.write(`data: ${JSON.stringify(body)}\n\n`);
  res.end();
}

function logRequest({ logger, level, traceId, tool, upstream, status, latencyMs }) {
  const write = resolveLogMethod(logger, level);
  write(
    JSON.stringify({
      trace_id: traceId,
      tool,
      upstream,
      status,
      latency_ms: latencyMs
    })
  );
}

async function readJsonBody(req) {
  const chunks = [];
  for await (const chunk of req) {
    chunks.push(chunk);
  }

  if (chunks.length === 0) {
    return {};
  }

  const raw = Buffer.concat(chunks).toString("utf8");
  try {
    return JSON.parse(raw);
  } catch {
    throw new AppError("Request body must be valid JSON", {
      code: ERROR_CODES.BAD_REQUEST,
      status: 400
    });
  }
}

function verifyAuth(config, req) {
  if (!config.mcpAuthToken) {
    return;
  }

  const authHeader = req.headers.authorization || "";
  const tokenFromHeader = authHeader.startsWith("Bearer ") ? authHeader.slice(7) : undefined;
  const token = tokenFromHeader || req.headers["x-mcp-auth-token"];

  if (token !== config.mcpAuthToken) {
    throw new AppError("Unauthorized", {
      code: ERROR_CODES.BAD_REQUEST,
      status: 401
    });
  }
}

function formatMappedError(error, traceId) {
  const normalized = normalizeError(error);
  const details = normalized.details;
  const code = normalizeErrorCode(normalized.code);

  const errorBody = {
    code,
    message: normalized.message,
    trace_id: traceId
  };

  if (details !== undefined) {
    errorBody.details = details;
  }

  return {
    status: normalized.status || 500,
    code,
    body: {
      ok: false,
      error: errorBody
    }
  };
}

export function createProtocolMcpServer(toolHandlers, { logger = console } = {}) {
  const mcpServer = new McpServer({
    name: "mcp-lan-gateway",
    version: "1.0.0"
  });

  function createMcpToolCallback(toolName) {
    const upstream = TOOL_UPSTREAM_PATH[toolName] || "unknown";

    return async (args) => {
      const traceId = createTraceId();
      const startAt = Date.now();

      try {
        const result = await toolHandlers[toolName](args || {}, { traceId });
        logRequest({
          logger,
          level: "info",
          traceId,
          tool: toolName,
          upstream,
          status: 200,
          latencyMs: Date.now() - startAt
        });

        return {
          content: [{ type: "text", text: JSON.stringify(result) }],
          structuredContent: result
        };
      } catch (error) {
        const formatted = formatMappedError(error, traceId);
        logRequest({
          logger,
          level: getErrorLogLevel(formatted.code),
          traceId,
          tool: toolName,
          upstream,
          status: formatted.status,
          latencyMs: Date.now() - startAt
        });

        const errorPayload = formatted.body.error;
        const toolErrorPayload = { error: errorPayload };

        return {
          isError: true,
          content: [{ type: "text", text: JSON.stringify(toolErrorPayload) }],
          structuredContent: toolErrorPayload
        };
      }
    };
  }

  mcpServer.registerTool(
    SEARCH_PROBLEMS_TOOL.name,
    {
      description: SEARCH_PROBLEMS_TOOL.description,
      inputSchema: SEARCH_PROBLEMS_ZOD_SCHEMA
    },
    createMcpToolCallback(SEARCH_PROBLEMS_TOOL.name)
  );

  mcpServer.registerTool(
    GET_PROBLEM_DETAIL_TOOL.name,
    {
      description: GET_PROBLEM_DETAIL_TOOL.description,
      inputSchema: GET_PROBLEM_DETAIL_ZOD_SCHEMA
    },
    createMcpToolCallback(GET_PROBLEM_DETAIL_TOOL.name)
  );

  return mcpServer;
}

function sendMcpTransportError(res, message, traceId, status = 400) {
  sendJson(res, status, {
    jsonrpc: "2.0",
    error: {
      code: -32000,
      message,
      data: { trace_id: traceId }
    },
    id: null
  });
}

export function createGatewayServer({
  config = loadConfig(),
  apiClient,
  enableMcpRegistration = true,
  logger = console
} = {}) {
  const client =
    apiClient ||
    new ApiClient({
      baseUrl: config.targetApiBaseUrl,
      timeoutMs: config.upstreamTimeoutMs
    });

  const tools = {
    search_problems: createSearchProblemsHandler({ apiClient: client }),
    get_problem_detail: createGetProblemDetailHandler({ apiClient: client })
  };

  const toolDefinitions = [SEARCH_PROBLEMS_TOOL, GET_PROBLEM_DETAIL_TOOL];

  let server;
  let mcpServer;
  const streamableSessions = new Map();

  async function executeTool(name, input, context) {
    const handler = tools[name];
    if (!handler) {
      throw new AppError(`Unknown tool: ${name}`, {
        code: ERROR_CODES.BAD_REQUEST,
        status: 400
      });
    }

    const result = await handler(input, context);
    return { ok: true, result };
  }

  async function handleMcpProtocolRequest(req, res, traceId) {
    verifyAuth(config, req);

    const parsedBody = req.method === "POST" ? await readJsonBody(req) : undefined;
    const sessionId = req.headers["mcp-session-id"];

    let session = sessionId ? streamableSessions.get(String(sessionId)) : undefined;

    if (!session) {
      if (req.method !== "POST" || !isInitializeRequest(parsedBody)) {
        sendMcpTransportError(res, "No valid MCP session provided", traceId, 400);
        return;
      }

      const transport = new StreamableHTTPServerTransport({
        sessionIdGenerator: () => randomUUID(),
        onsessioninitialized: (newSessionId) => {
          streamableSessions.set(newSessionId, session);
        }
      });
      const protocolServer = createProtocolMcpServer(tools, { logger });

      session = { transport, protocolServer };
      transport.onclose = async () => {
        const activeSessionId = transport.sessionId;
        if (activeSessionId) {
          streamableSessions.delete(activeSessionId);
        }
      };

      await protocolServer.connect(transport);
    }

    await session.transport.handleRequest(req, res, parsedBody);
  }

  async function handleToolRequest(req, res, parsedUrl) {
    const traceId = createTraceId();
    const startAt = Date.now();
    const toolName = parsedUrl.pathname.replace("/tools/", "");
    const upstream = TOOL_UPSTREAM_PATH[toolName] || "unknown";
    const sse = isSseRequest(req, parsedUrl);

    try {
      verifyAuth(config, req);
      const input = await readJsonBody(req);
      const payload = await executeTool(toolName, input, { traceId });

      const latencyMs = Date.now() - startAt;
      logRequest({ logger, level: "info", traceId, tool: toolName, upstream, status: 200, latencyMs });

      if (sse) {
        sendSse(res, 200, payload);
        return;
      }

      sendJson(res, 200, payload);
    } catch (error) {
      const formatted = formatMappedError(error, traceId);
      const latencyMs = Date.now() - startAt;
      logRequest({
        logger,
        level: getErrorLogLevel(formatted.code),
        traceId,
        tool: toolName,
        upstream,
        status: formatted.status,
        latencyMs
      });

      if (sse) {
        sendSse(res, formatted.status, formatted.body);
        return;
      }

      sendJson(res, formatted.status, formatted.body);
    }
  }

  async function handleRpcRequest(req, res, parsedUrl) {
    const traceId = createTraceId();
    const startAt = Date.now();
    const sse = isSseRequest(req, parsedUrl);
    let toolName = "unknown";

    try {
      verifyAuth(config, req);
      const body = await readJsonBody(req);
      toolName = body.tool;

      if (typeof toolName !== "string" || toolName.trim() === "") {
        throw new AppError("tool is required", {
          code: ERROR_CODES.BAD_REQUEST,
          status: 400
        });
      }

      const upstream = TOOL_UPSTREAM_PATH[toolName] || "unknown";
      const toolInput = body.input !== undefined ? body.input : body.arguments;
      const result = await executeTool(toolName, toolInput || {}, { traceId });
      const latencyMs = Date.now() - startAt;

      logRequest({
        logger,
        level: "info",
        traceId,
        tool: toolName,
        upstream,
        status: 200,
        latencyMs
      });

      if (sse) {
        sendSse(res, 200, result.result);
        return;
      }

      sendJson(res, 200, result.result);
    } catch (error) {
      const upstream = TOOL_UPSTREAM_PATH[toolName] || "unknown";
      const formatted = formatMappedError(error, traceId);
      const latencyMs = Date.now() - startAt;
      logRequest({
        logger,
        level: getErrorLogLevel(formatted.code),
        traceId,
        tool: toolName,
        upstream,
        status: formatted.status,
        latencyMs
      });

      if (sse) {
        sendSse(res, formatted.status, formatted.body);
        return;
      }
      sendJson(res, formatted.status, formatted.body);
    }
  }

  async function requestHandler(req, res) {
    const parsedUrl = new URL(req.url, `http://${req.headers.host || "127.0.0.1"}`);

    if (req.method === "GET" && parsedUrl.pathname === "/health") {
      sendJson(res, 200, { ok: true });
      return;
    }

    if (req.method === "GET" && parsedUrl.pathname === "/tools/list") {
      verifyAuth(config, req);
      sendJson(res, 200, {
        tools: toolDefinitions
      });
      return;
    }

    if (parsedUrl.pathname === "/mcp") {
      const traceId = createTraceId();
      try {
        await handleMcpProtocolRequest(req, res, traceId);
      } catch (error) {
        const normalized = normalizeError(error);
        const status = normalized.status === 401 ? 401 : normalized.status === 400 ? 400 : 500;
        sendMcpTransportError(res, normalized.message, traceId, status);
      }
      return;
    }

    if (req.method === "POST" && parsedUrl.pathname.startsWith("/tools/")) {
      await handleToolRequest(req, res, parsedUrl);
      return;
    }

    if (req.method === "POST" && parsedUrl.pathname === "/rpc") {
      await handleRpcRequest(req, res, parsedUrl);
      return;
    }

    const traceId = createTraceId();
    const formatted = formatMappedError(
      new AppError("Not found", {
        code: ERROR_CODES.NOT_FOUND,
        status: 404
      }),
      traceId
    );
    if (isSseRequest(req, parsedUrl)) {
      sendSse(res, formatted.status, formatted.body);
      return;
    }
    sendJson(res, formatted.status, formatted.body);
  }

  return {
    get mcpServer() {
      return mcpServer;
    },

    get baseUrl() {
      if (!server) {
        return null;
      }
      const address = server.address();
      if (!address || typeof address === "string") {
        return null;
      }
      const host = address.address === "::" || address.address === "0.0.0.0" ? "127.0.0.1" : address.address;
      return `http://${host}:${address.port}`;
    },

    async start() {
      if (enableMcpRegistration) {
        mcpServer = createProtocolMcpServer(tools, { logger });
      }

      server = http.createServer((req, res) => {
        requestHandler(req, res).catch((error) => {
          const traceId = createTraceId();
          const formatted = formatMappedError(error, traceId);
          sendJson(res, formatted.status, formatted.body);
        });
      });

      await new Promise((resolve) => {
        server.listen(config.mcpPort, config.mcpHost, resolve);
      });

      return this;
    },

    async stop() {
      for (const session of streamableSessions.values()) {
        await session.transport.close();
      }
      streamableSessions.clear();

      if (mcpServer) {
        await mcpServer.close();
      }

      if (!server) {
        return;
      }

      await new Promise((resolve, reject) => {
        server.close((error) => {
          if (error) {
            reject(error);
            return;
          }
          resolve();
        });
      });

      server = undefined;
    }
  };
}
