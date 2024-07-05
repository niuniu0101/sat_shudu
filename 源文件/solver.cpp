//����ļ��Ƕ�solver.h��CNF��������ֵ�ʵ�� 

#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<new>
#include<cassert>
#include "solver.h"
using namespace std;

int random=1;//���random==0����ʹ�á����������ԣ������ʹ�á������������
//�����ڷ������۲�����ԪLΪ�滹��Ϊ��ʱ�����һ��ʼ��cnf��+L�ĳ��ִ�����-L�����������棬���������ۼ�
//������ڷ������۲�����ԪLΪ�滹��Ϊ��ʱ������������滹�������ۼ� 


bool crossCNF::calculate(const char * const filename)
//��֤cnf�� res�ļ��Ƿ�ƥ�� 
{
	
	int *ans=new int[boolNum+1];//res�ļ������ݻᱻд��ans����cnf���бȽ� 
	int i,n;
	
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("�ļ���ʧ�ܣ����ܼ���\n");
		delete[] ans;
		return 0;
	}
	fscanf(fp,"%*s%d%*s",&n);
	if(n==0)
	{
		printf("�޽⣬������֤\n");
		return 0;
	}
	
	printf("res=[");
	for(i=0;i<boolNum;i++)
	{
		fscanf(fp,"%d",&n);
		if(n<0)ans[-n]=0;
		else ans[n]=1;
		printf("%d ",n);
	}
	bool ok;
	crossNode *p;
	printf("]\n���鿪ʼ\n");
	for(i=1;i<=clauseNum;i++)//��ÿ���Ӿ����ҵ���һ��ΪTrue�����֣��ҵ��ˣ�����Ӿ����True 
	{
		ok=false;
		p=clauses[i].right;
		while(p)
		{
			n=p->Bool;
			printf("%d ",n);
			if(n<0 && ans[-n]==0  || n>0 && ans[n]==1)
			{
				printf("True");
				ok=true;
				break;
			}
			
			
			p=p->right;
		}
		printf("\n");
		if(!ok)
		{
			printf("clause:False");//��������ĸ��Ӿ�ΪFalse��������cnfҲ��ΪFalse 
			fclose(fp);
			delete[] ans;
			return false;
		}
	}
	
	
	delete[] ans;
	fclose(fp);
	return true;
}

int crossCNF::changeBool(int x)
//�Ѹ��������һ�ֱȽϴ�������ĺ������Ա������������������� 
{
	return (x>0)?x:(2*boolNum+1+x);
}


bool crossCNF::solve(const char* const filename,bool display)
//����⣬��Ҫ������ΪinnerSolve�������컷�����ѽ��д���ļ�ʲô�� 
{
	
	FILE *fp=NULL;
	if(filename)fp=fopen(filename,"w");
	if(random)printf("��ǰ�����ԣ����\n");       
	else printf("��ǰ�����ԣ�����\n");
	
	
	int start_time=clock();//��ʼ��ʱ 
	bool ans=innerSolve();
	int delta_time=clock()-start_time;//������ʱ 
	
	if(ans)
	{
		//�н� 
		if(display)printf("�н� ��ʱ%dms\n",delta_time);
		hypo[0]=TRUE;
		if(fp)
		{
			fprintf(fp,"s 1\nv ");
		
			for(int i=1;i<=boolNum;i++)
			{
				if(hypo[i]==TRUE)fprintf(fp,"%d ",i);
				else if(hypo[i]==FALSE)fprintf(fp,"-%d ",i);
				else fprintf(fp,"-%d ",i);
			}
			
			fprintf(fp,"\nt %d",delta_time);
		}
			
		
	}
	else
	{
		//�޽�
		if(display)printf("�޽� ��ʱ%d\n",delta_time);
		hypo[0]=FALSE;
		if(fp)fprintf(fp,"s 0\n");
		
	}
	fclose(fp);
	
	
	
	return ans;

}

int crossCNF::believe(int L)
//����L==true������������innerSolve�໥���� 
{
	
	//��hypothesis��ע���� 
	if(L>0)hypo[L]=TRUE;
	else hypo[-L]=FALSE;
	//���á���ɾ����ջ 
	crossNode *DeleteNodesHead=NULL;
	//������ʱָ����� 
	crossNode *p,*q; 
	int i,target;
	int startNum=remainClauseNum;
	
	//ɾȥ���к�L���Ӿ� 
	for(q=bools[changeBool(L)].down;q;q=q->down)
	{
		
		if(q->del)continue;
		target=q->Clause;
		sum[target]++;
		remainClauseNum--;
		for(p=&clauses[target];p;p=p->right)
		{
			if(p->del)continue;
			p->del=true;      // �Ѿ���ɾ���� 
			
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
		// ɾ��������ô�� 
		//��������������Ӿ�
		if(sum[p->Clause]==0)
		{
			restore(L,startNum,DeleteNodesHead);
			return 0;
		}
		if(sum[p->Clause]==1)single.push(p->Clause);//���ɾ���˵��Ӿ䣬�Ͱ����ӵ������Ӿ䡱ջ��ȥ 
	}
	if(innerSolve())return 1;
	restore(L,startNum,DeleteNodesHead);
	return 0;
}
	
	
void crossCNF::restore(int L,int startNum,crossNode *Head)
//��believe���������޸ĸ�ԭ 
{
	
	hypo[abs(L)]=UNSURE;
	while(Head)//��ԭһЩ��� 
	{
		Head->del=false;
		sum[Head->Clause]++; 
		Head=Head->next;
	}
	remainClauseNum=startNum;
}

int crossCNF::innerSolve()
//ʵ�ʽ⣬���believe�໥���� 
{
	int i,L;
	crossNode *p;
	while(!single.empty())//��ͼ�ӡ����Ӿ䡱ջ�л�õ��Ӿ� 
	{
		L=single.pop();
		if(!clauses[L].del && sum[L]==1)
		{
			p=clauses[L].right;
			while(p->del)p=p->right;
			return believe(p->Bool);
		}
	}
	
	//ѡȡ����һ�е�һ���� ���ֽ��з������� �� ������� һ������õ� 
	
	for(i=1;i<=clauseNum;i++)
	{
		if(sum[i]==0) continue;   // ��ʣ�������Ϊ0 
		p=clauses[i].right;
		while(p && p->del)p=p->right;
		break;
	}
	L=abs(p->Bool);    // ת��Ϊ���� 
	
	//��ʼ�������ۣ�����Ҫ�����ȿ������Ļ����ȿ��Ǹ��� 
	if(random)L*=2*(rand()%2)-1;//�����ѡȡ���� 
	else L*=tendency[L];//����ѡȡ���� 
	
	if(believe(L))return 1;
	return believe(-L);
	
	
}


