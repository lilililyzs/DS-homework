#include <iostream>
#include<iomanip>
#include <queue>

using namespace std;

#if 0 // ÷–¥20
#include "graph.h"
int main(void) {
	adj_matrix M1;
	M1.construct_UI();
	M1.k_exists_UI();
	/*
		A    B    C    D    E    F 
	A		  1			1
	B  1					1			1
	C							   1
	D 1	  1                   1
	E               1     1          1
	F        1                   1
	*/
	unsigned int quit;
	cin >> quit;
	return 0;
}

#elif 0 // ÷–¥21
#include "graph.h"
int main(void) {
	digraph DG ;
	//DG.build_test();
	DG.build_test_3completed();
	DG.printVE();
	DG.Find_directed_simple_circuit();
	return 0;
}
#elif 1 // ÷–¥22
#include "graph.h"
int main(void) {
	digraph DG;
	DG.build_net_withADJM();
	/*input:
	8 11
	0 1 0 2 1 3 2 3 3 4 3 5 4 5 4 6 5 6 5 7 6 7
	0 1 2 0 2 3 1 3 2 2 3 1 3 4 2 3 5 4 4 5 1 4 6 2 5 6 2 5 7 1 6 7 3
	*/
	//DG.adjacenyMatrix.printMatrix();
	DG.printWeightedMatrix();
	DG.Prim();
	DG.printVE();
}
#endif // 0
