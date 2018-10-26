#include "BMinusTree.h"

BMinusTree::BMinusTree()
{
	root = NULL;
	NodeNum = 0;
}


BMinusTree::~BMinusTree()
{
}

SearchResult* BMinusTree::search(TreeNode* &node, Type key) {
	SearchResult* result = new SearchResult();
	if (node==NULL) {//���� �ս��
		result->isSearched = false;
		result->node = node;
		return result;
	}
	else {
		TreeNode* tempNode = node;
		for (int i = 0; i < node->keyNum; i++) {
			if (key < node->keyArray[i]) {//һ��������ǰ�ڵ��key���ֵ
				tempNode = node->childArray[i];//i���� ����û�о�û�ҵ�
				if (tempNode == NULL) {
					result->node = node;
					return result;
				}
				return search(tempNode, key);
			}
			else if (key == node->keyArray[i]) {//�ڽ�����ҵ��� ����ȥ
				result->isSearched = true;
				result->node = node;
				return result;
			}
			else {
				//key����node����һ��ֵ�����ҵ�key����nodeĳ����ֵ֮��
				if (key < node->keyArray[i + 1]||i==node->keyNum-1) {//��������ֵ�м�
					tempNode = node->childArray[i + 1];//���Һ���
					if (tempNode == NULL) {
						result->node = node;
						return result;
					}
					return search(tempNode, key);
				}
			}
		}

	}
}

/*�ӿں��������⿪�ŵ�����������λ�ú��Ƿ��ҵ�*/
SearchResult* BMinusTree::Search(Type key) {
	SearchResult* result = search(root,key);
	return result;
}

/*��������������
*/
void BMinusTree::SplitChild(TreeNode* node) {
	TreeNode* rightNode = new TreeNode();//�½������� Ȼ��ѵ�ǰ��Ϣ���� ���ڸ�ĸ��
	for (int i = childMin; i < degree; i++) {//iָ���м���ĺ�һ��
		rightNode->keyArray[i - childMin] = node->keyArray[i];//childmin��С�ӽڵ�����
		node->keyArray[i] = none;
		node->keyNum--;
		rightNode->keyNum++;
	}
	//������+1,������Ҫ���Ƕ�������һ��ָ��λ
	for (int i = childMin; i < childMax + 1; i++) {//������Ҫ���ѵ����
		if (node->childArray[i] == NULL) {
			break;
		}

		node->childArray[i]->parentNode = rightNode;//debug4 Сʱ ����������
		rightNode->childArray[i - childMin] = node->childArray[i];
		node->childArray[i] = NULL;
	}

	TreeNode * parentNode = node->parentNode;
	if (parentNode == NULL) {
		TreeNode* newRoot = new TreeNode();//���ڵ�Ϊ��Ҫ�䶯�����
		insertInNode(newRoot, node->keyArray[keyMin]);
		//�����������ϵ��Ѿ���λ�����ڵ��key
		node->keyArray[keyMin] = none;//ɾ���Ѿ����ڸ��ڵ���Ǹ�ֵ
		node->keyNum--;//���£���̫���׺����ˣ�ɾ���ͼ���Ҫ����

		newRoot->childArray[0] = node;
		newRoot->childArray[1] = rightNode;

		node->parentNode = newRoot;//�� ���ڵ����ӽ��
		rightNode->parentNode = newRoot;
		//����root
		root = newRoot;
	}
	else {//������ڵ㲻Ϊ�������µĴ������������ ���븸������ �ݹ���� �������û�� ����ɹ�
		int Index = insertInNode(parentNode, node->keyArray[keyMin]);
		//index�����½ڵ��ԭ�����׽ڵ�ĸ�����ֵ����
		//�����������ϵ��Ѿ���λ�����ڵ��key
		node->keyArray[keyMin] = none;
		node->keyNum--;//���£���̫���׺�����
		//�Ӳ���㿪ʼ�����Ƹ�ĸ�ڵ��ϵ�ָ��
		for (int i = Index + 1; i < childMax; i++) {
			parentNode->childArray[i + 1] = parentNode->childArray[i];
			//���ƶ��ӽڵ�ʹ�ҽ�����inedx
		}
		parentNode->childArray[Index + 1] = rightNode;
		rightNode->parentNode = parentNode;
		//�����ڵ��ʱ����
		if (parentNode->keyNum == degree) {
			SplitChild(parentNode);//�ݹ�
		}
	}

}

/*��ĳ��ֵ����ڵ㣬�����ز���λ��
*/
int BMinusTree::insertInNode(TreeNode* &node, Type key) {
	if (node->keyNum == 0) {
		node->keyArray[0] = key;
		node->keyNum++;
		return 0;//���ֵ�Ѵ���
	}
	else {
		int i = node->keyNum-1;//�Ӻ����
		while (i >= 0 && node->keyArray[i] > key) {
			node->keyArray[i + 1] = node->keyArray[i];//�ȵ�ǰ�Ĵ����λ
			i--;
		}
		node->keyArray[i + 1] = key;
		node->keyNum++;
		return (i + 1);
	}
	
}

/*��ĳ��ֵ����b-��*/
bool BMinusTree::Insert(Type key) {
	SearchResult * result = Search(key);
	TreeNode* node = result->node;
	bool isSearched = result->isSearched;//�Ѿ������ֵ ���벻�ɹ�
	if (isSearched) {
		return false;
	}
	else {
		//node is empty root ����
		if (node == NULL) {
			node = new TreeNode();
			root = node;
		}

		insertInNode(node, key);//�嵽node���
		NodeNum++;
		if (node->keyNum < degree) {
			return true;
		}
		else {
			SplitChild(node);//���˾ͷ���
		}

	}
}

/*δ��ɵ��Ƴ��㷨*/
bool BMinusTree::Remove(Type key) {
	SearchResult * result = Search(key);
	if (!result->isSearched) {
		return false;
	}
	if (!IsLeaf(result->node)) {
		for (int i = 0; i < result->node->keyNum; i++) {
			if (result->node->keyArray[i] == key) {
				result->node->keyArray[i] = result->node->childArray[i]->keyArray[0];
				//removeLeafKey();
			}
		}
	}
}

/*�ж�ĳ���ڵ��Ƿ���Ҷ�ڵ�*/
bool BMinusTree::IsLeaf(TreeNode * node) {
	for (int i = 0; i < childMax;i++) {
		if (node->childArray[i] != NULL) {
			return false;
		}
	}
	return true;
}

/*���ɲ��ظ������*/
set<Type> BMinusTree::getRandomNum(int num) {

	set<Type> set;
	srand((unsigned)time(NULL));
	while (set.size() < num) {
		set.insert(rand());
	}
	return set;
}

void BMinusTree::Output() {
	queue<TreeNode*> treeQueue;
	treeQueue.push(root);
	TreeNode *parent = NULL;
	int height = (int)ceil(log((NodeNum + 1) / 2) / log(childMin));
	int* levelArray = new int[height];
	for (int i = 0; i < height; i++) {
		levelArray[i] = 0;
	}
	int level = 0;
	levelArray[level] = 1;
	cout << endl << "root:" << endl;
	while (!treeQueue.empty()) {
		TreeNode* tempNode = treeQueue.front();
		treeQueue.pop();
		levelArray[level]--;
		cout << "[";
		for (int i = 0; i < tempNode->keyNum; i++) {
			cout << tempNode->keyArray[i] << " ";
		}
		cout << "]" << "	";
		if (levelArray[level] == 0) {
			cout << "\n";
			level++;
			cout<<"the "<<level+1<<" level:"<<"\n";
			parent = tempNode->parentNode;//�ø�ĸ���α��ס��ǰ�ĸ�ĸ
		}
		if (!IsLeaf(tempNode)) {
			int n = 0;
			for (int i = 0; i < childMax; i++) {
				if (tempNode->childArray[i] == NULL) {
					break;
				}
				treeQueue.push(tempNode->childArray[i]);
				n++;
			}
			if (parent == tempNode->parentNode) {
				levelArray[level] += n;
			}
			else {
				levelArray[level+1] += n;
			}
		}
	}
	cout << "null" << endl;

}
