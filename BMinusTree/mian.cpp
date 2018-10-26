#include"BMinusTree.h"
void main() {
	BMinusTree * bmt = new BMinusTree();
	cout << "-----------menu------------" << endl;
	cout << "insert, search, print, test(insert 2000 random numbers in tree and show) exit" << endl;
	cout << "opreration: ";
	string str = "";
	while (str != "exit") {
		
		cin >> str;
		switch (* str.c_str())
		{
		case 'i':
			cout << endl << "input an integer(> 0 ): ";
			Type key;
			cin >> key;
			if (bmt->Insert(key)) {
				cout << endl << "success!";
			}
			else
			{
				cout << endl << "failure";
			}
			
			break;
		case's':
			cout << endl << "input an integer(> 0 ): ";
			cin >> key;
			if (bmt->Search(key)->isSearched) {
				cout << endl << "success!";
			}
			else
			{
				cout << endl << "failure";
			}

			break;
		case'p':
			bmt->Output();
			break;
		case't': {
			int testNum = 2000;
			set<Type> a = bmt->getRandomNum(testNum);
			set<Type>::iterator it;
			for (it = a.begin(); it != a.end(); it++) {
				bmt->Insert(*it);
			}
			bmt->Output();
			break;
		}
				 
		default:
			cout << endl << "operation: ";
			break;
		}
	}

	
	
	/*int a[] = { 11, 2, 56, 58, 22, 130, 154,666, 826,999,1000};//for test
	for (int key : a) {
		bmt->Insert(key);
	}*/

	
	//SearchResult * result = bmt->Search(999);
}