#include "string.h"

/**
 * Custom string library implementation.
 * Avoiding standard string.h.
 */

int str_len(const char* s) {
    int len = 0;
    while(s[len]) len++;
    return len;
}

void str_copy(char* dest, const char* src) {
    int i = 0;
    while(src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int str_compare(const char* s1, const char* s2) {
    int i = 0;
    while(s1[i] && s2[i]) {
        if(s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

void int_to_str(int n, char* s) {
    int i = 0, isNegative = 0;
    
    if (n == 0) {
        s[i++] = '0';
        s[i] = '\0';
        return;
    }
    
    if (n < 0) {
        isNegative = 1;
        n = -n;
    }
    
    while (n != 0) {
        s[i++] = (n % 10) + '0';
        n /= 10;
    }
    
    if (isNegative) s[i++] = '-';
    
    s[i] = '\0';
    
    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

int str_to_int(const char* s) {
    int res = 0;
    int sign = 1;
    int i = 0;
    
    if (s[0] == '-') {
        sign = -1;
        i++;
    }
    
    while (s[i]) {
        res = res * 10 + (s[i] - '0');
        i++;
    }
    
    return res * sign;
}
