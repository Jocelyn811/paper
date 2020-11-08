#include <iostream>
#include<malloc.h>
#define Max 20 
typedef int VexType;
typedef VexType Mgraph[Max][Max];
 
//��������

Mgraph G1; //�ڽӾ���Ķ�ά������
int n, e;  //nΪ��������eΪ���� 
//*������


using namespace std;

//��ջ˳��洢���ʹ��Ľ��ͱ� 
struct StackNode
{
    int data;//ջ�ĵ�ǰջ��λ���±� 
    StackNode *next;//ָ��ߵĽ�� 
};

//��ջ���в���Ԫ��e����ջ 
void push(StackNode *&S,int e)
{
    StackNode *p=new StackNode;//����һ��ָ�� 
	p->data=e;//�ڵ�ǰ��ջ��λ�ò����ֵ 
    p->next=S; 
    S=p;//ָ����һ��λ�� 
}

//ɾ��ջ������ 
int pop(StackNode *&S)
{
	int e=S->data;//������ı߸�ֵ��e 
    StackNode *p=S;
	S=S->next;//ָ����һ���ڵ� 
	delete p;
    return e;//���ص��Ǳ�ֵ 
}
//�ڽӾ��� 
void creat_mg(Mgraph G) {
	int i,j,k;
	//����ͼ�������Ϣ
	cout<<"������ͼ�Ķ�������"<<endl;
	cin>>n; 
	cout<<"������ͼ�ı�����"<<endl; 
    cin>>e;
	//��ͼ�е�����ֵ��ֵΪ0�������������㶼�ǲ���ص� 
	//��ʼ�� ��Ӿ���
	//�ճ�G[][0],���ڼ�¼ 
	for(i = 1; i <= n ; i++) {
		for(j =1 ; j <= n ; j++)
			G[i][j] = 0;
	}
	//��ֵ 
	for(k = 1; k <= e; k++) {
	    cout<<"������֮����·������������vi , vj"<<endl; 
		cin>>i>>j;
		
		G[i][j] = 1; 
		G[j][i] = 1;
	}	 
}
 
//����ڽӾ���
void out_mg(Mgraph G) {
	int i ,j ,k;
	//������� 
	for(i = 1; i <= n; i++) {
		cout<<endl;
		for(j = 1; j <= n; j++) 
			cout<<G[i][j]<<" ";
	}
	//������ڱ�
	/* 
	cout<<endl;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			if(G[i][j] != 0)	
				cout<<"���ڱ�<"<<i<<","<<j<<">"<<endl;*/

}

//int vexnum=5;
//int *visited =(int*)malloc(G.n*sizeof(int));
int visited[20];//֮�����Ż����Կɲ����Զ�̬�������� 

void show(StackNode *&S)
{
	
	if(S)
	{
		
	    show(S->next);//������һ����� 
	    cout<<"v"<<S->data<<" ";//��ʾ����Ķ��� 
	}
}

//����������� 
void DFS(StackNode *&S,int v,int r ,Mgraph G)//vΪ��㣬rΪ�յ㶥�� 
{

	visited[v]=1;//�Ƚ��������� 
	push(S,v);
	if(v==r)//�жϵ�ǰ����յ��Ƿ���ͬ 
	{
		cout<<"����·����";
		show(S);
		cout<<endl;
	}
	for(int w=0;w<=n;w++)//����û�в���С�ڵ��ڵĻ�����ʾ�������һ������ 
	if(G[v][w] && (!visited[w]))//�жϾ����б��Ƿ�����Լ��ýڵ���û�б�ǹ�����������бߴ����ҽ��û�б���ǹ��������ýڵ��ٴν���������� 
	DFS(S,w,r,G); //���� 
	visited[v]=0; //�ͷű�ǣ����Եڶ��α���ʱ�����ý�� 
	pop(S);
	 
}


int main()
{
	int a, b;//a��ʾ��ʼ�˵㣬b��ʾ�����˵� 
    creat_mg(G1);
	out_mg(G1);
	cout<<endl;
    StackNode *S=NULL;
    cout<<"��������ʼ�˵�ͽ����˵㣺"<<endl;
    cin>>a>>b;
    DFS(S,a,b,G1);  
 return 0;
}

