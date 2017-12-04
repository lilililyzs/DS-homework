#ifndef GRAPH_H
#define GRAPH_H

typedef class adj_matrix {
public:
	int nV, nE;
	bool** M = nullptr;
	int* visitFlag = nullptr;
	adj_matrix();
	adj_matrix::~adj_matrix();
	/*��һ������*/
	void attachVE(int v, int e);	//apply new space
	void printMatrix(void);
	/*�ڶ��㴴��*/
	void construct_UI(void);//�û���������ͼ
	/*������ʹ��*/
	//��д20���ҵ�����ָ������֮���Ƿ����k���ȵ�·��
	bool k_exists(int k, int ini, int ter);
	int next_unvisited_adj(int vertex, int* visitflag);//��һ���ڽ���
	void  KPATH_dfs(bool &Ffind, int *visitFlag,int now, int end, int cnt);
	void k_exists_UI(void);
}adj_matrix;
adj_matrix::adj_matrix() {
	this->nV = this->nE = 0;
}
adj_matrix::~adj_matrix() {
	if (M != nullptr) {
		for (int i = 0; i < this->nV; i++)
			delete[] M[i];
		delete[] M;
	}
	free(this->visitFlag);
}
void adj_matrix::attachVE(int v, int e) {
	this->nV = v;
	this->nE = e;
	this->M = new bool*[v];
	for (int i = 0; i < v; i++)
		this->M[i] = new bool[v];
	for (int i = 0; i < v; i++)
		for (int j = 0; j < v; j++)
			this->M[i][j] = false;
}
void adj_matrix::printMatrix(void) {
	cout << "the adjacency matrix is like this:" << endl;
	cout << setw(5) << "r\\c";
	for (int c = 0; c < nV; c++)
		cout << setw(5) << c;
	cout << endl;
	for (int r = 0; r < nV; r++) {
		cout << setw(5) << r;
		for (int c = 0; c < nV; c++)
			if (this->M[r][c]) cout << setw(5) << '1';
			else cout << setw(5) << '0';
			cout << endl;
	}
}
void adj_matrix::construct_UI(void) {
	cout << "please input the number of vertices and edges" << endl;
	cin >> this->nV >> this->nE;
	attachVE(this->nV, this->nE);
	cout << "please input the initial and terminal vertex of each edge (index start by 0):" << endl;
	int r, c;
	for (int i = 0; i < this->nE; i++) {
		cin >> r >> c;
		this->M[r][c] = true;
		this->M[c][r] = true;
	}
	this->visitFlag =(int*) malloc( sizeof(int)*this->nV);
	for (int i = 0; i < this->nV; i++) 
this->visitFlag[i] = -1;
	printMatrix();
}
void adj_matrix::k_exists_UI(void) {
	int k, ini, ter;
	cout << "Please input k, initial vertex and terminal vertex:" << endl;
	cin >> k >> ini >> ter;
	if (k_exists(k, ini, ter)) cout << "this path long "<<k<<" exists" << endl;
	else cout << "this path long " << k << " does not exists" << endl;
}
int adj_matrix::next_unvisited_adj(int vertex, int *visitflag) {
	for (int c = 0; c <this-> nV; c++)
		if (M[vertex][c] && visitflag[c] < 0 && c != vertex) return c;
	return -1;
}
bool adj_matrix::k_exists(int k, int ini, int ter) {
	if (k > this->nV - 1 || ini > this->nV || ter > nV)		return false;
	bool Ffind = false;
	this->visitFlag[0] = 1;
	KPATH_dfs(Ffind, visitFlag, ini, ter, k);
	delete[] visitFlag;
	return Ffind;
}
void  adj_matrix::KPATH_dfs(bool &Ffind, int *visitFlag, int now, int end, int cnt) {
	if (Ffind) return;
	if (cnt == 0 && now == end) {
		Ffind = true;
		return;
	}
	visitFlag[now] = 1;
	int next;
	while (!Ffind&&(next = next_unvisited_adj(now, visitFlag) )!= -1) {
		KPATH_dfs(Ffind, visitFlag, next, end, cnt - 1);
		visitFlag[next] = -1;
	}
}

typedef struct arcnode {
    int  info;//1ʱΪ����arc��10ʱΪ����
	int adjvex; //int ��vexnode��������������������ͼ������ָ�ñߵ�terminal vertex��
	arcnode * nextarc;
	arcnode(int info, int adjvex, arcnode* nextarc);
}arcnode;
arcnode::arcnode(int info, int adjvex, arcnode* nextarc) {
	this->info=info ; this->adjvex=adjvex; this->nextarc=nextarc;
}
typedef struct vexnode {
	char vexdata;
	int outdegree = 0;
	arcnode * firstarc;//�Ӹýڵ�����ĵ�һ����
	vexnode(char a, arcnode* b);
	void cnt_out(void);
}vexnode;
vexnode::vexnode(char a, arcnode* b) {
	vexdata = a; firstarc = b;
}
void vexnode::cnt_out(void) {
	arcnode* p = firstarc;
	while (p) {
		outdegree++;
		p = p->nextarc;
	}
}
typedef class digraph {//���ڽӱ��ʾ������ͼ
public:
	int nV, nE;
	vexnode ** vertices;
	//��һ�㽨��
	digraph(void);
	~digraph(void);
	void build_test(void);
	void build_test_3completed(void);
	void initialize_UI(void);//TODO
	//�ڶ��㹫�ù���
	void printVE(void);
	//���������⹦��
	//��д��21��
	void Find_directed_simple_circuit(void);
	void dfs_CC(int* visitFlag,int* solution,int current,int k);//DFS�ݹ���Ѱ��
};
digraph::digraph(void) {
	nV = nE = 0;
	vertices = NULL;
	cout << "a digraph has been created" << endl;
}
digraph::~digraph(void) {//TODO����delete
	if (vertices) {
		for (int i = 0; i < nV; i++) delete vertices[i];
		delete[] vertices;
	}
}
void digraph::build_test(void) {
	nV = 6; nE = 7;
	vertices = new vexnode*[nV];
	for (int i = 0; i < nV; i++)  vertices[i]=new vexnode('A'+i,NULL);
	vertices[0]->firstarc = new arcnode(1, 5,NULL);
	vertices[1]->firstarc = new arcnode(1, 0, new arcnode(1, 2, NULL));
	vertices[2]->firstarc = new arcnode(1, 3, NULL);
	vertices[3]->firstarc = new arcnode(1, 4, NULL);
	vertices[4]->firstarc = new arcnode(1, 1, NULL);
	vertices[5]->firstarc = new arcnode(1, 4, NULL);
	for (int i = 0; i < nV; i++)  vertices[i]->cnt_out();
	cout << "a test digraph has been initialized" << endl;
}
void digraph::build_test_3completed(void) {
	nV = 3; nE = 6;
	vertices = new vexnode*[nV];
	for (int i = 0; i < nV; i++)  vertices[i] = new vexnode('A' + i, NULL);
	vertices[0]->firstarc = new arcnode(1, 1, new arcnode(1,2,NULL));
	vertices[1]->firstarc = new arcnode(1, 2, new arcnode(1, 0, NULL));
	vertices[2]->firstarc = new arcnode(1, 0, new arcnode(1,1,NULL));
	for (int i = 0; i < nV; i++)  vertices[i]->cnt_out();
	cout << "a test completed digraph has been initialized" << endl;
}
void digraph::initialize_UI(void) {
	cout << "please input the numbers of vertices and edges:" << endl;
	cin >> this->nV >> this->nE;

}
void digraph::printVE(void) {
	arcnode* p;
	cout << "the adjacency list of digraph:"<<endl;
	for (int i = 0; i < nV; i++) {
		cout << vertices[i]->vexdata;
		p = vertices[i]->firstarc;
		while (p) {
			cout << "->" << vertices[p->adjvex]->vexdata;
			p = p->nextarc;
		}
		cout << endl;
	}
}
void digraph::Find_directed_simple_circuit(void) {
	int *visitFlag = new int[this->nV];	for (int i = 0; i < this->nV;i++)	visitFlag[i] = -1;//����0��ʾ�õ��ѱ���
	int *solution = new int[this->nV];	for (int i = 0; i < this->nV;i++)	solution[i] = -1;//����·��
	dfs_CC(visitFlag, solution, 0, 0);
	delete[] visitFlag;
}
void digraph::dfs_CC(int* visitFlag, int* solution, int current,int k) {
	if (!this->vertices[current]->firstarc)//·���յ㣨�õ�û�г���)
		return;
	else if (visitFlag[current] > 0) //�л������·��
	{
		int qidian=-1;
		while (solution[++qidian] != current);
		cout << "find a circut: ";
		while (qidian < k) {
			cout << this->vertices[solution[qidian]]->vexdata << "->"; 
			qidian++;
		}
		cout << vertices[current]->vexdata<<endl;
	}
	else//��û���ֻ�
	{
		visitFlag[current] = 1;
		solution[k] = current;
		arcnode * p = vertices[current]->firstarc;
		while (p) {
			dfs_CC(visitFlag, solution, p->adjvex, k + 1);
			visitFlag[p->adjvex] = -1; solution[k + 1] = -1;//���ݻ�ԭ
			p = p->nextarc;
		}
	}
}
#endif