#include <windows.h>
#include <string.h>

#include "copy_to_clipboard.h"

int copy_to_clip(const char* encodedurl) {
    const size_t len = strlen(encodedurl) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), encodedurl, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    return 0;
}