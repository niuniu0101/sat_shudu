

#include<cstdio>


using namespace std;
#define MAXN 10000

enum BOOLVALUE {UNSURE, FALSE, TRUE};




struct crossNode
//ʮ������ڵ� 
{
	
	int Bool;//��ʾ�Լ��Ĳ�����Ԫ 
	int Clause;//��ʾ�Լ����Ӿ�
	bool del;
	crossNode *up,*down,*right,*left,*next;
	crossNode()
	{
		Bool=0;
		Clause=0;
		up=NULL;
		down=NULL;
		right=NULL;
		left=NULL;
		next=NULL;
		del=false;
	}

};

struct intStack
//intջ������ʹ������ջ 
//��ô�̵Ĵ���Ͳ�дcpp�ļ��� 
{
	int S[MAXN];
	int i=0;
	void push(int value)
	{
		S[i++]=value;
	}
	
	int pop()
	{
		//assert(i>0);
		return S[--i];
	}

	bool empty()
	{
		return i==0;
	}

};

class crossCNF
//ʮ������cnf 
{
	public:
		
		crossCNF(const char * const filename);//���캯�� 
		crossCNF(FILE *fp);//���캯�����ļ�ָ��棩 
		~crossCNF();//�������� 
		bool calculate(const char * const filename);//���� 
		void print(FILE *);//��ӡ 
		bool solve(const char* const filename,bool display);//����� 
		
	private:
		int boolNum;//������Ԫ���� 
		int clauseNum;//�Ӿ������ԭ���ģ� 
		int remainClauseNum;//ɾ��һЩ֮��ʣ�µ��Ӿ���� 
		int *sum;//ÿ���Ӿ��ʣ�����ָ��� 
		int *tendency;//ÿ�����ֵġ����� 
		crossNode *bools;//��Ŵ�1��ʼ 
		crossNode *clauses;//��Ŵ�1��ʼ 
		BOOLVALUE *hypo;//����ʱʹ�õġ����衱 
		intStack single;//�浥�Ӿ��ջ 
		
		void addNode(int,int);//��ӽ�㣬����cnf����ʱҪ�� 
		int changeBool(int);//��[-boolNum,-1]U[1,boolNum]�����[1,2*boolNum]�ĺ��� 
		int innerSolve();//ʵ�ʽ� 
		int believe(int);//�����š������庬���뿴solver.cpp 
		void restore(int L,int startNum,crossNode *Head);//�ָ���believe�����޸Ĺ���cnf 
		
};



		

		
		
		
		
	
