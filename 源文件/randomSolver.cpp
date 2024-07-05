#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<new>
#include<cassert>
#include "solver.h"


int remainBoolNum;
int *ans;
int order[600];
int b[600];
void randomFill(int a[],int n)
//��a��1~nλ���������1~n 
{
	printf("randonFill(%d)\n",n);
	int i,j,m;
	for(i=1;i<=n;i++)a[n]=0;
	for(i=1;i<=n;i++)
	{
		m=rand()%(n+1-i)+1;
		//ѡȡ��m��
		for(j=1;j<=n;j++)
		{
			if(!b[j])
			{
				m--;
				if(m==0)
				{
					a[i]=j;
					b[j]=1;
					break;
				}
			}
			
		}
	}
	
}

int crossCNF::randomSolve(int Ans[])
{
	srand(clock());
	ans=Ans;
	remainBoolNum=boolNum;
	randomFill(order,boolNum);
	printf("order=[");
	for(int i=1;i<=boolNum;i++)printf("%d ",order[i]);
	printf("]\n");
	randomInnerSolve(1);
	return 1;
}


int crossCNF::randomBelieve(int L,int level)
//����L==true 
{
	
	//��hypothesis��ע���� 
	if(L>0)hypo[L]=TRUE;
	else hypo[-L]=FALSE;
	remainBoolNum--;
	
	//���á���ɾ����ջ 
	crossNode *DeleteNodesHead=NULL;
	
	
	crossNode *p,*q;//����ͷ��㣬ֱȡ��һ�� 
	int i,target;
	//int advice=0;
	int startNum=remainClauseNum;
	
	
	//ɾȥ���к�L���Ӿ� 
	for(q=bools[changeBool(L)].down;q;q=q->down)
	{
		
		if(q->del)continue;
		
		//ɾ��q���ڵ��Ӿ� 
		target=q->Clause;
		//ɾȥ���Ϊtarget���Ӿ䣡
		
			
		sum[target]++;
		remainClauseNum--;
		for(p=&clauses[target];p;p=p->right)
		{
			if(p->del)continue;
			p->del=true; 
			//��p����DeleteNodesջ 
			p->next=DeleteNodesHead;
			DeleteNodesHead=p;
			sum[target]--;
		}
	}
	
	
	//�������ʣ���Ӿ�����Ϊ0 ,����Ϊ������� 
	if(remainClauseNum==0)return 1;
	//��Ҫɾȥ�����Ӿ��е�-L 
	for(p=bools[changeBool(-L)].down;p;p=p->down)
	{
		if(p->del)continue;
		p->del=true;
		p->next=DeleteNodesHead;
		DeleteNodesHead=p;
		
		sum[p->Clause]--;
		
		
		//Ҳ�����ǿ�������������Ӿ�
		if(sum[p->Clause]==0)
		{
			restore(L,startNum,DeleteNodesHead);
			remainBoolNum++;
			return 0;
		}
		if(sum[p->Clause]==1)
		{
			
			single.push(p->Clause);
		}
	}
	
	
	
	if(randomInnerSolve(level))//�˴�level+1 
	{
		remainBoolNum++;
		return 1;
	}
	
	
	
	remainBoolNum++;
	restore(L,startNum,DeleteNodesHead);
	return 0;
	
	
}
	
	


int crossCNF::randomInnerSolve(int level)
{
	//printf("???\n");
	int i,L=0;
	crossNode *p;
	
{//���Ӿ䲿�� 
	while(!single.empty())
	{
		L=single.pop();
		if(!clauses[L].del && sum[L]==1)
		{
			
			p=clauses[L].right;
			while(p->del)p=p->right;
			return randomBelieve(p->Bool,level);
		}
	}
	
	if(single.i==0)
	{
		for(L=1;L<=clauseNum;L++)
		{
			if(!clauses[L].del && sum[L]==1)
			{
				p=clauses[L].right;
				while(p->del)p=p->right;
				return randomBelieve(p->Bool,level);
			}
		}
	}
}
	
	
	
	
	
	//ѡȡ����һ�е�һ���� 
//	for(i=1;i<clauseNum;i++)
//	{
//		if(sum[i]==0)continue;
//		p=clauses[i].right;
//		while(p && p->del)p=p->right;
//		
//		break;
//		
//	}
//	L=p->Bool;

//���ѡȡ��
	 

//{//��L
//	int remainBoolNum=0,random;
//	
//	for(i=1;i<=boolNum;i++)if(hypo[i]==UNSURE)remainBoolNum++;	
//	 assert(remainBoolNum);
//	int random=rand()%remainBoolNum+1;
//	for(i=1;i<=boolNum;i++)
//	{
//		if(hypo[i]==UNSURE)
//		{
//			random--;
//			if(random==0)
//			{
//				L=i;
//				break;
//			}
//		}
//	}
	//�������
	i=level;
	
	L=order[i];
	while(hypo[L]!=UNSURE)
	{
		i++;
		L=order[i];
	}
	if(!(1<=L && L<=boolNum && 1<=level))
	{
		printf("%d %d\n",L,level);
	}
	assert(1<=L && L<=boolNum && 1<=level);
	
	L*=2*(rand()%2)-1;
	
//{//��һ���ط� 
//	if(randomBelieve(L))return 1;
//	else return randomBelieve(-L);
//}


{//��С���編
	int ans1=randomBelieve(L,level+1);
	int ans2;
	if(ans1==0)
	{
		return randomBelieve(-L,level+1);
	}
	else if(ans1==1)
	{
		ans2=randomBelieve(-L,level+1);
		if(ans2==0)return 1;
		if(ans2==1)
		{
			for(i=1;i<=boolNum;i++)ans[i]=(hypo[i]==TRUE)?1:0;
			
			return 2;
		}
		return 2;
		
	}
	else if(ans1==2)
	{
		return 2;
	}
}


}
	
	



