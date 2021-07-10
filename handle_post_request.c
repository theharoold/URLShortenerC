// Example from curl documentation: https://curl.se/libcurl/c/getinmemory.html

#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "handle_post_request.h"

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

struct MemoryStruct handle_post_request(struct MemoryStruct chunk, const char* post_input) {

    CURL *curl_handle;
    CURLcode res;
    
    char* post_field = malloc(strlen(post_input)+4);
    strcpy(post_field, "url=");
    strcat(post_field, post_input);
    printf("%s field\n", post_field);
    
 
    curl_global_init(CURL_GLOBAL_ALL);
 
    /* init the curl session */
    curl_handle = curl_easy_init();
 
    /* specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, CLEANURI_API_LINK);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, post_field);
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0);

 
    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
    /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
    /* get it! */
    res = curl_easy_perform(curl_handle);
 
    /* check for errors */
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
    }
    else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */
 
        printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
    }
 
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    printf("RESULT: %s",chunk.memory);
 
    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();

    return chunk;
}