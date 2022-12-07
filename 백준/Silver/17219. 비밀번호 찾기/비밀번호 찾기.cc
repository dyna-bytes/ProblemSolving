#include <stdio.h>
#include <string.h>
#include <memory.h>

#define MAX_KEY 32
#define MAX_VALUE 32
#define MAX_TABLE 131072
typedef unsigned long ul;

struct Hash {
    char key[MAX_KEY + 1];
    char value[MAX_VALUE + 1];
} tb[MAX_TABLE];

ul hash(const char* str) {
    ul hash = 5381;
    char ch;
    while (ch = *str++) 
        hash = ((hash << 5) + hash + ch) % MAX_TABLE;
    return hash % MAX_TABLE;
}

char* find(const char* key) {
    ul h = hash(key);
    int cnt = MAX_TABLE;
    while (tb[h].key[0] && cnt--) {
        if (strcmp(tb[h].key, key) == 0) 
            return tb[h].value;
        h = (h + 1) % MAX_TABLE;   
    }
    return 0;
}

bool add(const char* key, const char* value) {
    ul h = hash(key);
    while (tb[h].key[0]) {
        if (strcmp(tb[h].key, key) == 0)
            return false;
        h = (h + 1) % MAX_TABLE;
    }

    strcpy(tb[h].key, key);
    strcpy(tb[h].value, value);
    return true;
}

int main() {
    int N, Q; scanf("%d %d", &N, &Q);

    for (int i = 0; i < N; i++) {
        char url[MAX_KEY]; 
        char password[MAX_VALUE];
        scanf("%s %s", &url, &password);
        add(url, password);
    }

    for (int i = 0; i < Q; i++) {
        char url[MAX_KEY];
        scanf("%s", &url);
        char* ret = find(url);
        printf("%s\n", ret);
    }

    return 0;
}