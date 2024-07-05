
#include<cstdio>
#include<cstring>
#include<stdexcept>
#include<iostream>
#include<cmath> 
#include<ctime>
#include "Hanidoku.h"
#include "solver.h"
using namespace std;



int translate_hive(int i,int j,int k)//三元坐标转化为绝对坐标 
{
	return ((i<=5?(i*(i+7)/2-5):(i*(29-i)/2-35))+j)*9+k;
}


void head(FILE* fp)
{
	int i,j,k,k1,k2,x,y;
	//蜂窝数独 
	
	for(i=1;i<=9;i++)//格约束 
	{
		for(j=1;j<=9-abs(i-5);j++)
		{
			//每个格子需要填一个数字
			for(k=1;k<=9;k++)
			{
				fprintf(fp,"%d ",translate_hive(i,j,k));
			}
			fprintf(fp,"0\n");

			for(k1=1;k1<=8;k1++)
			{
				for(k2=k1+1;k2<=9;k2++)
				{
					fprintf(fp,"-%d -%d 0\n",translate_hive(i,j,k1),translate_hive(i,j,k2));
				}
			}
		}
	}
	
	//表示查重开始
	int side;
	

	//可见，范围是x in [1,abs(i-5)],forall x:y in [10-abs(i-5),9-abs(i-5)+x] 
	
	
	//行查重开始
	for(i=1;i<=9;i++)
	{
		//对于第i行
		int A=abs(i-5);//表示不确定需不需要选的边缘的宽度 
		
		//[1,abs(i-5)]和[10-abs(i-5),9]是不确定选不选的，[abs(i-5)+1,9-abs(i-5)]是必选的
		
		for(k=A+1;k<=9-A;k++)
		{
			//k必须要在此行出现
			for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(i,j,k));
			fprintf(fp,"0\n");
		}
		
		for(x=1;x<=A;x++)
		{
			for(y=10-A;y<=9-A+x;y++)
			{
				//x,y至少有一个要在此行出现
				for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(i,j,x));
				for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(i,j,y));
				fprintf(fp,"0\n");
			}
		}
		
		for(k=1;k<=9;k++)
		{
			//第i行不能同时出现两个k
			for(k1=1;k1<=9-A-1;k1++)
			{
				for(k2=k1+1;k2<=9-A;k2++)
				{
					fprintf(fp,"-%d -%d 0\n",translate_hive(i,k1,k),translate_hive(i,k2,k));
				}
			}
		}
		
		
	}
	
	//行查重结束，升斜线查重开始
	for(i=1;i<=9;i++)
	{
		/*
		第i条升斜线的第1个位置可以表示为 
		{
			51,61,71,81,91,92,93,94,95
			也即
			i<=5:(4+i,1)
			i>5 :(9,i-4)
		}
		第i条升斜线的第j个位置可以表示为 
		{
			x=x1-j
			y=min(y1+j,i)
			
		}
		*/
		int A=abs(i-5);
		int x1=(i<=5)?(4+i):9;
		int y1=(i<=5)?1:(i-4);
		int x,y;
		
		for(k=A+1;k<=9-A;k++)
		{
		
			
			for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(x1+1-j,min(y1-1+j,i),k));
			fprintf(fp,"0\n");
		}
		
		for(x=1;x<=A;x++)
		{
			for(y=10-A;y<=9-A+x;y++)
			{
				for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(x1+1-j,min(y1-1+j,i),x));
				for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(x1+1-j,min(y1-1+j,i),y));
				fprintf(fp,"0\n");
			}
		}
		
		for(k=1;k<=9;k++)
		{
			//第i升斜线不能同时出现两个k
			for(k1=1;k1<=9-A-1;k1++)
			{
				for(k2=k1+1;k2<=9-A;k2++)
				{
					fprintf(fp,"-%d -%d 0\n",translate_hive(x1+1-k1,min(y1-1+k1,i),k),translate_hive(x1+1-k2,min(y1-1+k2,i),k));
				}
			}
		}
	}
	
	//降斜线查重开始 
	for(i=1;i<=9;i++)
	{
		//在升直线的基础上，令x=10-x即可 
		int A=abs(i-5);
		int x1=(i<=5)?(4+i):9;
		int y1=(i<=5)?1:(i-4);
		int x,y;
		
		for(k=A+1;k<=9-A;k++)
		{
		
			
			for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(10-(x1+1-j),min(y1-1+j,i),k));
			fprintf(fp,"0\n");
		}
		
		for(x=1;x<=A;x++)
		{
			for(y=10-A;y<=9-A+x;y++)
			{
				for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(10-(x1+1-j),min(y1-1+j,i),x));
				for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(10-(x1+1-j),min(y1-1+j,i),y));
				fprintf(fp,"0\n");
			}
		}
		
		for(k=1;k<=9;k++)
		{
			//第i升斜线不能同时出现两个k
			for(k1=1;k1<=9-A-1;k1++)
			{
				for(k2=k1+1;k2<=9-A;k2++)
				{
					fprintf(fp,"-%d -%d 0\n",translate_hive(10-(x1+1-k1),min(y1-1+k1,i),k),translate_hive(10-(x1+1-k2),min(y1-1+k2,i),k));
				}
			}
		}
	}
	//表示查重结束 
	
	
}



void reduction(int &i,int &j,int &k,int n)//绝对坐标翻译为三元坐标 
{
	int i2,j2;
	k=n%9;
	if(k==0)
	{
		k=9;
		n-=9;
	}
	n/=9;
	
	//现在n= (i<=5?(i*(i+7)/2-5):(i*(29-i)/2-35))+j
	if(n<=34)
	{
		//第一路径： 
		for(i2=1;i2<=5;i2++)
		{
			j2=n-(i2*(i2+7)/2-5);
			if(1<=j2 && j2<=9-abs(i2-5))
			{
				
				i=i2;
				j=j2;
				return;
			}
		}
	}
	else
	{
	
		for(i2=6;i2<=9;i2++)
		{
			j2=n-(i2*(29-i2)/2-35);
			
			if(1<=j2 && j2<=9-abs(i2-5))
			{
				i=i2;
				j=j2;
				return;
			}
		}
	}
		

}



Hanidoku::Hanidoku()
//空数独
{
	for(int i=0;i<9;i++)for(int j=0;j<9;j++)map[i][j]=0;
} 


void Hanidoku::load(const char* const filename)
//从res文件中读取 
{
	FILE *fp=fopen(filename,"r");
	while(fgetc(fp)!='v');//一直读取到v为止
	int i,j,k,n,t;
	for(i=0;i<9;i++)for(j=0;j<9;j++)map[i][j]=0;
	
	for(t=0;t<549;t++)
	{
		fscanf(fp,"%d",&n);
		if(n>0)
		{
			reduction(i,j,k,n);
			cell(i,j)=k;
		}
	}
	fclose(fp);
	return;
}





int& Hanidoku::cell(int x,int y)
//取第x行第y个格子，xy从1开始 
{
	if(!legal(x,y))throw runtime_error("Sudoku.cell不合法访问");
	return map[x-1][y-1];
}

bool Hanidoku::legal(int x,int y)
//一个坐标是否合法 
{
	
	if(x<1 or x>9 or y<1 or y>9-abs(x-5))
		return false;
	return true;
}

void Hanidoku::print()
{
	
	
	int i,j,k,d;
	for(i=0;i<5;i++)
	{
		d=abs(i-4);
		for(j=0;j<2*d+1;j++)printf(" ");
		for(j=0;j<9-d;j++)printf("/ \\ ");
		printf("\n");
		for(j=0;j<2*d;j++)printf(" ");
		for(j=0;j<9-d;j++)printf("| %c ",(map[i][j])?(map[i][j]+'0'):'.');
		printf("|\n"); 
	}
	for(j=0;j<9;j++)printf(" \\ /");
	printf("\n");
	for(i=5;i<9;i++)
	{
		
		d=abs(i-4);
		
		for(j=0;j<2*d;j++)printf(" ");
		for(j=0;j<9-d;j++)printf("| %c ",(map[i][j])?(map[i][j]+'0'):'.');
		printf("|\n"); 
		for(j=0;j<2*d+1;j++)printf(" ");
		for(j=0;j<9-d;j++)printf("\\ / ");
		printf("\n");
	}
			
	
	
}

void Hanidoku::generate_cnf(const char* const filename)
//根据Sudoku生成对应的cnf 
{
	FILE *fp=fopen(filename,"w");//新建文件
	fprintf(fp,"c generated by cnf_developer.generate_cnf()\np cnf ");
	int extra_line=content_num();//S有多少个点，cnf就在原来的基础上多多少行
	int i,j;
	
	//549变量，基础2500行
	fprintf(fp,"549 %d\n",7468+content_num());
	head(fp);
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=9-abs(i-5);j++)
		{
			if(cell(i,j))
			{
				fprintf(fp,"%d 0\n",translate_hive(i,j,cell(i,j)));
			}
		}
	}
	
	
	fclose(fp);
	
}

int Hanidoku::content_num()
//返回自己已经填了的格子的数量 
{
	int n=0,i,j;
	for(i=0;i<9;i++)for(j=0;j<9;j++)if(map[i][j])n++;
	return n;
}	


void Hanidoku::randomGenerate(int n)
//生成随机数独题目，n为提示数 
{
	int i,j,m;
	bool broke;
	for(i=0;i<9;i++)for(j=0;j<9;j++)map[i][j]=0;  //初始化 
	
	if(n==0)return;
	
	generate_cnf("temp\\tempCNF.cnf");
	crossCNF cnf("temp\\tempCNF.cnf");

	cnf.solve("temp\\tempRES.res",false);//主要耗时 

	load("temp\\tempRES.res");

	
	
	int del=0;
	while(61-del>n)
	{
		//随机挑选一个元素进行删除
		m=rand()%(61-del);
		broke=false;
		for(i=1;i<=9&&!broke;i++)
		{
			for(j=1;j<=9-abs(i-5);j++)
			{
				if(cell(i,j))
				{
					m--;
					if(m==0)
					{
						cell(i,j)=0;
						del++;
						broke=true;
						break;
					}
				}
			}
		}
		
	}
	

}



