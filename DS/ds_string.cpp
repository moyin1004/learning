#include "ds_string.h"

void StrAssign(SString &T, char s[]);
void StrCopy(SString &T, SString S);
bool StrEmpty(SString &S) {
    return (S.length == 0);
}

int StrLength(SString &S) {
    return S.length;
}

void ClearString(SString &S) {
    S.length = 0;
}

void DestoryString(SString &S) {
    S.length = 0;
}

bool Concat(SString &T, SString &S1, SString &S2);
bool SubString(SString &Sub, SString S, int pos, int len) {
    if (pos+len-1 > S.length) return false;
    for (int i = pos; i < pos+len; ++i) {
        Sub.ch[i-pos] = S.ch[i];
    }
    Sub.length = len;
    return true;
}

int Index(SString S, SString T) {      // KMP
    return 1;
}

int StrCompare(SString S, SString T) { // S > T return > 0; S < T return < 0;
    for (int i = 0; i < S.length && i < T.length; ++i) {
        if (T.ch[i] != S.ch[i]) {
            return S.ch[i] - T.ch[i];
        }
    }
    // 长度长的大
    return S.length-T.length;
}