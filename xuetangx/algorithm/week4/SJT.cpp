#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n,k;
    scanf("%d%d",&n,&k);
    vector<int> vec(n+1);
    for(int i=1; i<=n; i++) vec[i]=i;
    vector<int>d(n+1);
    for(int i=1; i<=n; i++) d[i]=-1;
    for(int r=1; r<=k-1; ++r)
    {
        int mobile_int=0;
        int pos=0;
        for(int i=1; i<=n; i++)
        {
            int j=i+d[i];
            if(j==0||j>n||vec[j]>vec[i]) continue;
            if(vec[i]>mobile_int)
            {
                mobile_int=vec[i];
                pos=i;
            }
        }
        int tpos=pos+d[pos];
        swap(vec[pos],vec[tpos]);
        swap(d[pos],d[tpos]);
        for(int i=1; i<=n; i++)
        {
            if(vec[i]>mobile_int) d[i]=-d[i];
        }
    }
    for(int i=1; i<n; ++i)
    {
        printf("%d ",vec[i]);
    }
    printf("%d\n",vec[n]);
    return 0;
}