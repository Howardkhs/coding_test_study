#include<cstdio>

using namespace std;

int main()
{
	long long n,arr[10]={0,};
	scanf("%lld",&n);
	for(int i=0;i<10;i++)
	{
		long long bias = 1;
		while(bias<=n)
		{
			long long l = n/bias/10;
			long long target = (n/bias)%10;
			long long r = n%bias;
			if(i==0)
			{
				if(target == i && bias != 1)
				{
					arr[i] += (l-1) * bias + r + 1;
				}
				else{
					arr[i] += l*bias;
				}
			}
			else{
				if(target == i)
				{
					arr[i] += l * bias + r + 1;
				}
				else if(target < i)
				{
					arr[i] += l * bias;
				}
				else{
					arr[i] += (l+1) * bias;
				}
			}
			bias *= 10; 
			//printf("%d\n",arr[i]);
		}
		printf("%lld ",arr[i]);
	}
}
/*
���й���
�� �ڸ������� �ش��ϴ� ���ڰ� ����� �������� ����غ���
*/ 
