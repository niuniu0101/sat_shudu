
#include<cstdio>
#include<cstring>
#include<stdexcept>
#include<iostream>
#include<cmath> 
#include<ctime>
#include "Hanidoku.h"
#include "solver.h"
using namespace std;



int translate_hive(int i,int j,int k)//��Ԫ����ת��Ϊ�������� 
{
	return ((i<=5?(i*(i+7)/2-5):(i*(29-i)/2-35))+j)*9+k;
}


void head(FILE* fp)
{
	int i,j,k,k1,k2,x,y;
	//�������� 
	
	for(i=1;i<=9;i++)//��Լ�� 
	{
		for(j=1;j<=9-abs(i-5);j++)
		{
			//ÿ��������Ҫ��һ������
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
	
	//��ʾ���ؿ�ʼ
	int side;
	

	//�ɼ�����Χ��x in [1,abs(i-5)],forall x:y in [10-abs(i-5),9-abs(i-5)+x] 
	
	
	//�в��ؿ�ʼ
	for(i=1;i<=9;i++)
	{
		//���ڵ�i��
		int A=abs(i-5);//��ʾ��ȷ���費��Ҫѡ�ı�Ե�Ŀ�� 
		
		//[1,abs(i-5)]��[10-abs(i-5),9]�ǲ�ȷ��ѡ��ѡ�ģ�[abs(i-5)+1,9-abs(i-5)]�Ǳ�ѡ��
		
		for(k=A+1;k<=9-A;k++)
		{
			//k����Ҫ�ڴ��г���
			for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(i,j,k));
			fprintf(fp,"0\n");
		}
		
		for(x=1;x<=A;x++)
		{
			for(y=10-A;y<=9-A+x;y++)
			{
				//x,y������һ��Ҫ�ڴ��г���
				for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(i,j,x));
				for(j=1;j<=9-A;j++)fprintf(fp,"%d ",translate_hive(i,j,y));
				fprintf(fp,"0\n");
			}
		}
		
		for(k=1;k<=9;k++)
		{
			//��i�в���ͬʱ��������k
			for(k1=1;k1<=9-A-1;k1++)
			{
				for(k2=k1+1;k2<=9-A;k2++)
				{
					fprintf(fp,"-%d -%d 0\n",translate_hive(i,k1,k),translate_hive(i,k2,k));
				}
			}
		}
		
		
	}
	
	//�в��ؽ�������б�߲��ؿ�ʼ
	for(i=1;i<=9;i++)
	{
		/*
		��i����б�ߵĵ�1��λ�ÿ��Ա�ʾΪ 
		{
			51,61,71,81,91,92,93,94,95
			Ҳ��
			i<=5:(4+i,1)
			i>5 :(9,i-4)
		}
		��i����б�ߵĵ�j��λ�ÿ��Ա�ʾΪ 
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
			//��i��б�߲���ͬʱ��������k
			for(k1=1;k1<=9-A-1;k1++)
			{
				for(k2=k1+1;k2<=9-A;k2++)
				{
					fprintf(fp,"-%d -%d 0\n",translate_hive(x1+1-k1,min(y1-1+k1,i),k),translate_hive(x1+1-k2,min(y1-1+k2,i),k));
				}
			}
		}
	}
	
	//��б�߲��ؿ�ʼ 
	for(i=1;i<=9;i++)
	{
		//����ֱ�ߵĻ����ϣ���x=10-x���� 
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
			//��i��б�߲���ͬʱ��������k
			for(k1=1;k1<=9-A-1;k1++)
			{
				for(k2=k1+1;k2<=9-A;k2++)
				{
					fprintf(fp,"-%d -%d 0\n",translate_hive(10-(x1+1-k1),min(y1-1+k1,i),k),translate_hive(10-(x1+1-k2),min(y1-1+k2,i),k));
				}
			}
		}
	}
	//��ʾ���ؽ��� 
	
	
}



void reduction(int &i,int &j,int &k,int n)//�������귭��Ϊ��Ԫ���� 
{
	int i2,j2;
	k=n%9;
	if(k==0)
	{
		k=9;
		n-=9;
	}
	n/=9;
	
	//����n= (i<=5?(i*(i+7)/2-5):(i*(29-i)/2-35))+j
	if(n<=34)
	{
		//��һ·���� 
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
//������
{
	for(int i=0;i<9;i++)for(int j=0;j<9;j++)map[i][j]=0;
} 


void Hanidoku::load(const char* const filename)
//��res�ļ��ж�ȡ 
{
	FILE *fp=fopen(filename,"r");
	while(fgetc(fp)!='v');//һֱ��ȡ��vΪֹ
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
//ȡ��x�е�y�����ӣ�xy��1��ʼ 
{
	if(!legal(x,y))throw runtime_error("Sudoku.cell���Ϸ�����");
	return map[x-1][y-1];
}

bool Hanidoku::legal(int x,int y)
//һ�������Ƿ�Ϸ� 
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
//����Sudoku���ɶ�Ӧ��cnf 
{
	FILE *fp=fopen(filename,"w");//�½��ļ�
	fprintf(fp,"c generated by cnf_developer.generate_cnf()\np cnf ");
	int extra_line=content_num();//S�ж��ٸ��㣬cnf����ԭ���Ļ����϶������
	int i,j;
	
	//549����������2500��
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
//�����Լ��Ѿ����˵ĸ��ӵ����� 
{
	int n=0,i,j;
	for(i=0;i<9;i++)for(j=0;j<9;j++)if(map[i][j])n++;
	return n;
}	


void Hanidoku::randomGenerate(int n)
//�������������Ŀ��nΪ��ʾ�� 
{
	int i,j,m;
	bool broke;
	for(i=0;i<9;i++)for(j=0;j<9;j++)map[i][j]=0;  //��ʼ�� 
	
	if(n==0)return;
	
	generate_cnf("temp\\tempCNF.cnf");
	crossCNF cnf("temp\\tempCNF.cnf");

	cnf.solve("temp\\tempRES.res",false);//��Ҫ��ʱ 

	load("temp\\tempRES.res");

	
	
	int del=0;
	while(61-del>n)
	{
		//�����ѡһ��Ԫ�ؽ���ɾ��
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



