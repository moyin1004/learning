#ifndef __STRING__
#define __STRING__

#define MAXLEN 255

typedef struct {
    char ch[MAXLEN];
    int length;
} SString;

void StrAssign(SString &T, char s[]);
void StrCopy(SString &T, SString S);
bool StrEmpty(SString &S);
int StrLength(SString &S);
void ClearString(SString &S);
void DestoryString(SString &S);
bool Concat(SString &T, SString &S1, SString &S2);
bool SubString(SString &Sub, SString S, int pos, int len);
int StrIndex(SString &S, SString &T);      // KMP
int StrCompare(SString &S, SString &T); // S > T return > 0; S < T return < 0;

typedef struct {
    char *ch;
    int length;
} HString;

void StrAssign(HString &T, char s[]);
void StrCopy(HString &T, HString S);
bool StrEmpty(HString &S);
int StrLength(HString &S);
void ClearString(HString &S);
void DestoryString(HString &S);
bool Concat(HString &T, HString &S1, HString &S2);
bool SubString(HString &Sub, HString S, int pos, int len);
int StrIndex(HString S, HString T);      // KMP
int StrCompare(HString S, HString T); // S > T return > 0; S < T return < 0;

typedef struct StringNode {
    //char ch; // 存储密度低
    char ch[4];
    struct StringNode *next;
} StringNode, *String;

void BuildNext(SString &T);
void BuildNextval(SString &T);

#endif