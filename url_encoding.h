#ifndef encoder_h
#define encoder_h

const char* urlencode(const char* originalText);
void remove_backslash(char s[]);
char* extract_url(char url[]);

#endif