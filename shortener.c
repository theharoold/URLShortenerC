#include <stdlib.h> 
#include "url_encoding.h"
#include "copy_to_clipboard.h"

int main(int argc, char* argv[]) {
    
    // First argument is the executable file 
    // Second argument is the url to be shortened
    if (argc != 2) {
        return -1;
    }
    const char* url = argv[1];
    const char* encoded_url = malloc(sizeof(url)*3 + 1);
    encoded_url = urlencode(url);
    copy_to_clip(encoded_url);

    return 0;
}