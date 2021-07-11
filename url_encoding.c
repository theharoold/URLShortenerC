// CREDIT: https://gist.github.com/jesobreira

#include <stdlib.h>
#include <string.h>

#include "url_encoding.h"

const char* urlencode(const char* originalText)
{
    // allocate memory for the worst possible case (all characters need to be encoded)
    char *encodedText = (char *)malloc(sizeof(char)*strlen(originalText)*3+1);
    
    const char *hex = "0123456789abcdef";
    
    int pos = 0;
    for (int i = 0; i < strlen(originalText); i++) {
        if (('a' <= originalText[i] && originalText[i] <= 'z')
            || ('A' <= originalText[i] && originalText[i] <= 'Z')
            || ('0' <= originalText[i] && originalText[i] <= '9')) {
                encodedText[pos++] = originalText[i];
            } else {
                encodedText[pos++] = '%';
                encodedText[pos++] = hex[originalText[i] >> 4];
                encodedText[pos++] = hex[originalText[i] & 15];
            }
    }
    encodedText[pos] = '\0';
    return encodedText;
}

void remove_backslash(char s[])
{
    char c = '\\';
    int j = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] != c) {
            s[j] = s[i];
            ++j;
        }
    }
    s[j] = '\0';
}

char* extract_url(char url[])
{
    // {"result_url":""} has 17 characters
    int new_size = strlen(url) - 17;
    int end_of_url = strlen(url) - 2;

    char* buffer = malloc(new_size);
    memcpy(buffer, &url[15], new_size - 1);
    *(buffer + new_size - 1) = '\0';
    return buffer;
}