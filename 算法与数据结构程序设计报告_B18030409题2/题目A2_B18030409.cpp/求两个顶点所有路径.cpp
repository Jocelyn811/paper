#include <iostream>
#include<malloc.h>
#define Max 20 
typedef int VexType;
typedef VexType Mgraph[Max][Max];
 
//函数声明

Mgraph G1; //邻接矩阵的二维数组名
int n, e;  //n为顶点数，e为边数 
//*主函数


using namespace std;

//堆栈顺序存储访问过的结点和边 
struct StackNode
{
    int data;//栈的当前栈顶位置下标 
    StackNode *next;//指向边的结点 
};

//在栈顶中插入元素e，入栈 
void push(StackNode *&S,int e)
{
    StackNode *p=new StackNode;//创建一个指针 
	p->data=e;//在当前的栈顶位置插入边值 
    p->next=S; 
    S=p;//指向下一个位置 
}

//删除栈顶操作 
int pop(StackNode *&S)
{
	int e=S->data;//将链表的边赋值给e 
    StackNode *p=S;
	S=S->next;//指向下一个节点 
	delete p;
    return e;//返回的是边值 
}
//邻接矩阵 
void creat_mg(Mgraph G) {
	int i,j,k;
	//输入图的相关信息
	cout<<"请输入图的顶点数："<<endl;
	cin>>n; 
	cout<<"请输入图的边数："<<endl; 
    cin>>e;
	//将图中的所有值赋值为0，即任意两个点都是不相关的 
	//初始化 领接矩阵
	//空出G[][0],便于记录 
	for(i = 1; i <= n ; i++) {
		for(j =1 ; j <= n ; j++)
			G[i][j] = 0;
	}
	//赋值 
	for(k = 1; k <= e; k++) {
	    cout<<"请输入之间有路径的两个顶点vi , vj"<<endl; 
		cin>>i>>j;
		
		G[i][j] = 1; 
		G[j][i] = 1;
	}	 
}
 
//输出邻接矩阵
void out_mg(Mgraph G) {
	int i ,j ,k;
	//输出矩阵 
	for(i = 1; i <= n; i++) {
		cout<<endl;
		for(j = 1; j <= n; j++) 
			cout<<G[i][j]<<" ";
	}
	//输出所在边
	/* 
	cout<<endl;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			if(G[i][j] != 0)	
				cout<<"存在边<"<<i<<","<<j<<">"<<endl;*/

}

//int vexnum=5;
//int *visited =(int*)malloc(G.n*sizeof(int));
int visited[20];//之后再优化试试可不可以动态生成数组 

void show(StackNode *&S)
{
	
	if(S)
	{
		
	    show(S->next);//回溯下一个结点 
	    cout<<"v"<<S->data<<" ";//显示输出的顶点 
	}
}

//深度优先搜索 
void DFS(StackNode *&S,int v,int r ,Mgraph G)//v为起点，r为终点顶点 
{

	visited[v]=1;//先将起点做标记 
	push(S,v);
	if(v==r)//判断当前点和终点是否相同 
	{
		cout<<"存在路径：";
		show(S);
		cout<<endl;
	}
	for(int w=0;w<=n;w++)//这里没有不是小于等于的话会显示不出最后一个顶点 
	if(G[v][w] && (!visited[w]))//判断矩阵中边是否存在以及该节点有没有标记过，如果矩阵中边存在且结点没有被标记过，则进入该节点再次进行深度搜索 
	DFS(S,w,r,G); //回溯 
	visited[v]=0; //释放标记，可以第二次遍历时经过该结点 
	pop(S);
	 
}


int main()
{
	int a, b;//a表示起始端点，b表示结束端点 
    creat_mg(G1);
	out_mg(G1);
	cout<<endl;
    StackNode *S=NULL;
    cout<<"请输入起始端点和结束端点："<<endl;
    cin>>a>>b;
    DFS(S,a,b,G1);  
 return 0;
}

