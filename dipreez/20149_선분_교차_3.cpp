#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

int ccw(long long x1,long long y1,long long x2,long long y2,long long x3,long long y3)
{
	long long v_x1 = x2-x1,v_y1 = y2-y1,v_x2 = x3-x2,v_y2 = y3-y2;
	long long ccw = v_x1*v_y2 - v_x2*v_y1;
	if(ccw>0) return 1;
	else if(ccw==0) return 0;
	else return -1;
}

int main()
{
	long long x1,x2,x3,x4,y1,y2,y3,y4;
	scanf("%lld %lld %lld %lld\n%lld %lld %lld %lld",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
	int ccw1,ccw2,ccw3,ccw4;
	ccw1 = ccw(x1,y1,x2,y2,x3,y3);
	ccw2 = ccw(x1,y1,x2,y2,x4,y4);
	ccw3 = ccw(x3,y3,x4,y4,x1,y1);
	ccw4 = ccw(x3,y3,x4,y4,x2,y2);
	bool result =false;
	if(ccw1 * ccw2 == 0 && ccw3 * ccw4 == 0)
	{
			if(x1>x2)
			{
				swap(x1,x2);
				swap(y1,y2);
			}
			else if(x1==x2 && y1>y2)
			{
				swap(x1,x2);
				swap(y1,y2);
			}
			if(x3>x4)
			{
				swap(x3,x4);
				swap(y3,y4);
			}
			else if(x3==x4 && y3>y4)
			{
				swap(x3,x4);
				swap(y3,y4);
			}
			if((x2>x3?true:(x2==x3?y2>=y3:false))&&(x1<x4?true:(x1==x4?y1<=y4:false)))
			{
				printf("1\n");
				if(ccw1!=ccw2 && ccw3!=ccw4)
				{
					if(x2==x3 && y2==y3 || x2==x4 && y2==y4) printf("%lld %lld",x2,y2);
					else printf("%lld %lld",x1,y1);
				}
				else{
					if(x2==x3 && y2==y3) printf("%lld %lld",x2,y2);
					else if(x1==x4 && y1==y4) printf("%lld %lld",x1,y1);
				}
				return 0;
			}
	}
	else if(ccw1 * ccw2 <= 0 && ccw3 * ccw4 <= 0)
	{
		printf("1\n");
		long double grad1,grad2,c1,c2;
		bool is_ver1=false,is_ver2=false;
		if(x1-x2==0) is_ver1 =true;
		else
		{
			grad1 = (long double)(y1-y2) / (x1-x2);
		}
		if(x3-x4==0) is_ver2=true;
		else
		{
			grad2 = (long double)(y3-y4)/(x3-x4);
		}
		if(is_ver1)
		{
			c2 = y3 - grad2 * x3;
			long double y_meet;
			y_meet = grad2 * x1 + c2;
			printf("%.16Lf %.16Lf",(long double)x1,y_meet);
		}
		else if(is_ver2)
		{
			c1 = y1 - grad1 * x1;
			long double y_meet;
			y_meet = grad1 * x3 + c1;
			printf("%.16Lf %.16Lf",(long double)x3,y_meet);
		}
		else
		{
			c1 = y1 - grad1 * x1;
			c2 = y3 - grad2 * x3;
			long double x_meet,y_meet;
			x_meet = (c2 - c1) / (grad1 - grad2);
			y_meet = x_meet * grad1 + c1;
			printf("%.16Lf %.16Lf",x_meet,y_meet);
		}
		return 0;
	}
	printf("0");
}
/*
선분교차 2의 심화버전
ccw를 이용해 겹침여부를 확인하고
교점의 좌표는 우리가 잘 아는 1차함수, 기울기 등을 long double로 구현해서 풀면 된다.
해당 문제보다는 선분교차 2의 내용이 핵심 
*/ 
