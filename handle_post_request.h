#ifndef handle_post_req_h
#define handle_post_req_h

#include <stddef.h>

#define CLEANURI_API_LINK "https://cleanuri.com/api/v1/shorten"

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
struct MemoryStruct handle_post_request(struct MemoryStruct chunk, const char* post_input);

#endif