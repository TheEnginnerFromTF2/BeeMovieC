#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void print_highlighted_line(const char* line) {
    int len = strlen(line);
    if (len == 0) return;
    const int chars_per_sec = 20; 
    const int sleep_ms = 1000 / chars_per_sec;

    for (int i = 1; i <= len; i++) {
        printf("\r"); 
        printf("\033[1;33m%.*s\033[0m", i, line);
        printf("%s", line + i);
        fflush(stdout);

        Sleep(sleep_ms);
    }
    printf("\n");
}

int main() {
    SetConsoleTitle("The Bee Movie");
    HRSRC hRes = FindResource(NULL, "BEEMOVIE", RT_RCDATA);
    if (!hRes) {
        fprintf(stderr, "Error: Resource not found!\n");
        return 1;
    }

    HGLOBAL hData = LoadResource(NULL, hRes);
    void* pData = LockResource(hData);
    DWORD size = SizeofResource(NULL, hRes);
    char* writableData = (char*)malloc(size + 1);
    memcpy(writableData, pData, size);
    writableData[size] = '\0';
    char* line = strtok(writableData, "\r\n");
    while (line) {
        print_highlighted_line(line);
        line = strtok(NULL, "\r\n");
    }

    free(writableData);
    return 0;
}
