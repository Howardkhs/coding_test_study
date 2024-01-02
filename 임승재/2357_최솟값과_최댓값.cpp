#include<cstdio>
#include<vector>

using namespace std;

pair<int,int> seg[2000020];
int arr[1000010];

void create_seg(int idx,int l,int r)
{
	if(l==r)
	{
		seg[idx] = make_pair(arr[l],arr[l]);
		return;
	}
	int mid = (l+r)/2;
	create_seg(2*idx,l,mid);
	create_seg(2*idx+1,mid+1,r);
	int min,max;
	if(seg[2*idx].first<seg[2*idx+1].first) min = seg[2*idx].first;
	else min = seg[2*idx+1].first;
	if(seg[2*idx].second>seg[2*idx+1].second) max = seg[2*idx].second;
	else max = seg[2*idx+1].second;
	seg[idx] = make_pair(min,max);
}

pair<int,int> get_minmax(int idx,int l,int r,int begin,int end)
{
	if(r<begin || l>end) return make_pair(1000000001,0);
	if(l>=begin && r<=end) return seg[idx];
	else{
		int mid = (l+r)/2;
		pair<int,int> tmp1,tmp2;
		tmp1 = get_minmax(idx*2,l,mid,begin,end);
		tmp2 = get_minmax(idx*2+1,mid+1,r,begin,end);
		int min,max;
		if(tmp1.first<tmp2.first) min = tmp1.first;
		else min = tmp2.first;
		if(tmp1.second>tmp2.second) max = tmp1.second;
		else max = tmp2.second;
		return make_pair(min,max);
	}
}

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	create_seg(1,0,n-1);
	/*
	for(int i=0;i<2*n;i++)
	{
		printf("%d,%d ",seg[i].first,seg[i].second);
	}
	*/
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		pair<int,int> result;
		result = get_minmax(1,0,n-1,a-1,b-1);
		printf("%d %d\n",result.first,result.second);
	}
}
