(function () {
  async function request(url, parse) {
    const response = await fetch(url);
    if (!response.ok) {
      const error = new Error(`Request failed: ${response.status} ${url}`);
      error.status = response.status;
      throw error;
    }
    return parse(response);
  }

  async function getJSON(url) {
    return request(url, (response) => response.json());
  }

  async function getText(url) {
    return request(url, (response) => response.text());
  }

  window.RbookApi = { getJSON, getText };
}());
