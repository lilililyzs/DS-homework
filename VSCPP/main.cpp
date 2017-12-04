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

#elif 1 // ÷–¥21
#include "graph.h"
int main(void) {
	digraph DG ;
	//DG.build_test();
	DG.build_test_3completed();
	DG.printVE();
	DG.Find_directed_simple_circuit();
	return 0;
}
#endif // 0
