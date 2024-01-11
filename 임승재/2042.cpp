#include<cstdio>

using namespace std;

long long seg[4000010];
long long tmp[1000010];

long long init(int start,int end,int idx)
{
    if(start == end)
    {
        seg[idx] = tmp[start];
        return seg[idx];
    }
    int mid = (start+end)/2;
    return seg[idx] = init(start,mid,idx*2) + init(mid+1,end,idx*2+1);
}

void change(int start,int end,int idx,int target,long long diff)
{
    if(start>target || end<target) return;
    seg[idx] += diff;
    if(start==end) return;
    int mid = (start+end)/2;
    change(start,mid,idx*2,target,diff);
    change(mid+1,end,idx*2+1,target,diff);
}

long long sum(int start,int end,int idx,int l,int r)
{
    if(start>r || end<l) return 0;
    if(l<=start && end<=r) return seg[idx];
    else{
        int mid = (start+end)/2;
        return sum(start,mid,idx*2,l,r) + sum(mid+1,end,idx*2+1,l,r);
    }
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&tmp[i]);
    }
    init(0,n-1,1);

    for(int i=0;i<m+k;i++)
    {
        long long a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        if(a==1)
        {
            change(0,n-1,1,b-1,c-tmp[b-1]);
            tmp[b-1] = c;
        }
        else{
            printf("%lld\n",sum(0,n-1,1,b-1,c-1));
        }
    }
}
/*
세그먼트 트리
*/