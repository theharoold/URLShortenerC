#include <stdlib.h> 
#include <stdio.h>

#include "url_encoding.h"
#include "copy_to_clipboard.h"
#include "handle_post_request.h"



int main(int argc, char* argv[]) {
    
    // First argument is the executable file 
    // Second argument is the url to be shortened
    if (argc != 2) {
        return -1;
    }

    const char* url = argv[1];

    // The URL needs to be encoded
    const char* encoded_url = malloc(sizeof(url)*3 + 1);
    encoded_url = urlencode(url);

    // MemoryStruct is used for curl's POST json response
    // The shortened URL will be available in json format
    // in the chunk.memory attribute
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);  
    chunk.size = 0;    

    // Sending a post request with libcurl
    // And returning the structure
    chunk = handle_post_request(chunk, (const char*) encoded_url);
    
    // Copies the shortened url to clipboard, using windows.h
    copy_to_clip(chunk.memory);

    free(chunk.memory);
    return 0;
}
 
