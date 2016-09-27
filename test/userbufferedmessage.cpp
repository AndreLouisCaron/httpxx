#include <cassert>
#include <cstring>
#include <string>
#include <httpxx/UserBufferedMessage.hpp>
#include <iostream>

static const char *req1 =
  "POST /index.html HTTP/1.1\r\n"
  "Host: www.example.com\r\n"
  "Content-Length: 13\r\n"
  "\r\n"
  "Hello, world!\r\n";

static size_t req1len = strlen(req1);

static const char *req2 =
  "POST /index.html HTTP/1.1\r\n"
  "Host: www.example.com\r\n"
  "\r\n";

static size_t req2len = strlen(req2);

static const char *resp1 =
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/plain\r\n"
  "Content-Length: 13\r\n"
  "\r\n"
  "Hello, world!";

static size_t resp1len = strlen(resp1);

static const char *resp2 =
  "HTTP/1.1 200 OK\r\n"
  "Host: 192.168.1.1\r\n"
  "Content-Length: 0\r\n"
  "\r\n";

static size_t resp2len = strlen(resp2);

static void test_req(const char *data,
		     size_t datalen,
		     const char *content) {
  std::string str;
  http::UserBufferedRequest<std::string> parser(str);

  int used = 0;
  while (used < datalen) {
    used += parser.feed(data + used, datalen - used);
  }

  assert(used == datalen);
  assert(parser.headers_complete());
  assert(parser.complete());
  if (content)
    assert(str == content);
  else
    assert(str.length() == 0);
}

static void test_resp(const char *data,
		      size_t datalen,
		      const char *content) {
  std::string str;
  http::UserBufferedResponse<std::string> parser(str);
  int used = 0;
  while (used < datalen) {
    used += parser.feed(data + used, datalen - used);
  }

  assert(used == datalen);
  assert(parser.headers_complete());
  assert(parser.complete());
  if (content)
    assert(str == content);
  else
    assert(str.length() == 0);
}

int main() {
  test_req(req1, req1len, "Hello, world!");
  test_req(req2, req2len, NULL);

  test_resp(resp1, resp1len, "Hello, world!");
  test_resp(resp2, resp2len, NULL);

  return 0;
}
