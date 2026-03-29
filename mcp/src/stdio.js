import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js";

import { loadConfig } from "./config.js";
import { ApiClient } from "./client/apiClient.js";
import { createSearchProblemsHandler } from "./tools/searchProblems.js";
import { createGetProblemDetailHandler } from "./tools/getProblemDetail.js";
import { createProtocolMcpServer } from "./server.js";

const config = loadConfig();
const apiClient = new ApiClient({
  baseUrl: config.targetApiBaseUrl,
  timeoutMs: config.upstreamTimeoutMs
});

const mcpServer = createProtocolMcpServer({
  search_problems: createSearchProblemsHandler({ apiClient }),
  get_problem_detail: createGetProblemDetailHandler({ apiClient })
});

const transport = new StdioServerTransport();
await mcpServer.connect(transport);
