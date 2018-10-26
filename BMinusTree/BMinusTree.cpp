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
	if (node==NULL) {//特判 空结点
		result->isSearched = false;
		result->node = node;
		return result;
	}
	else {
		TreeNode* tempNode = node;
		for (int i = 0; i < node->keyNum; i++) {
			if (key < node->keyArray[i]) {//一旦遇到当前节点比key大的值
				tempNode = node->childArray[i];//i左孩子 左孩子没有就没找到
				if (tempNode == NULL) {
					result->node = node;
					return result;
				}
				return search(tempNode, key);
			}
			else if (key == node->keyArray[i]) {//在结点中找到了 跳出去
				result->isSearched = true;
				result->node = node;
				return result;
			}
			else {
				//key大于node最大的一个值或者找到key介于node某两个值之间
				if (key < node->keyArray[i + 1]||i==node->keyNum-1) {//夹在两个值中间
					tempNode = node->childArray[i + 1];//找右孩子
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

/*接口函数，对外开放的搜索，返回位置和是否找到*/
SearchResult* BMinusTree::Search(Type key) {
	SearchResult* result = search(root,key);
	return result;
}

/*将已满子树分裂
*/
void BMinusTree::SplitChild(TreeNode* node) {
	TreeNode* rightNode = new TreeNode();//新建右子树 然后把当前信息放入 连在父母上
	for (int i = childMin; i < degree; i++) {//i指向中间结点的后一个
		rightNode->keyArray[i - childMin] = node->keyArray[i];//childmin最小子节点数量
		node->keyArray[i] = none;
		node->keyNum--;
		rightNode->keyNum++;
	}
	//绝望的+1,这里需要考虑多留出的一个指针位
	for (int i = childMin; i < childMax + 1; i++) {//遍历到要分裂的情况
		if (node->childArray[i] == NULL) {
			break;
		}

		node->childArray[i]->parentNode = rightNode;//debug4 小时 认贼作父！
		rightNode->childArray[i - childMin] = node->childArray[i];
		node->childArray[i] = NULL;
	}

	TreeNode * parentNode = node->parentNode;
	if (parentNode == NULL) {
		TreeNode* newRoot = new TreeNode();//父节点为根要变动根结点
		insertInNode(newRoot, node->keyArray[keyMin]);
		//消除左子树上的已经进位到父节点的key
		node->keyArray[keyMin] = none;//删掉已经放在父节点的那个值
		node->keyNum--;//可怕，这太容易忽略了，删掉和加上要并行

		newRoot->childArray[0] = node;
		newRoot->childArray[1] = rightNode;

		node->parentNode = newRoot;//让 父节点认子结点
		rightNode->parentNode = newRoot;
		//更新root
		root = newRoot;
	}
	else {//如果父节点不为空做以下的处理（分两种情况 插入父亲满了 递归分裂 插入后父亲没满 插入成功
		int Index = insertInNode(parentNode, node->keyArray[keyMin]);
		//index用来新节点和原来父亲节点的各个数值排序
		//消除左子树上的已经进位到父节点的key
		node->keyArray[keyMin] = none;
		node->keyNum--;//可怕，这太容易忽略了
		//从插入点开始，后移父母节点上的指针
		for (int i = Index + 1; i < childMax; i++) {
			parentNode->childArray[i + 1] = parentNode->childArray[i];
			//后移儿子节点使右结点插在inedx
		}
		parentNode->childArray[Index + 1] = rightNode;
		rightNode->parentNode = parentNode;
		//若父节点此时满了
		if (parentNode->keyNum == degree) {
			SplitChild(parentNode);//递归
		}
	}

}

/*将某个值插入节点，并返回插入位置
*/
int BMinusTree::insertInNode(TreeNode* &node, Type key) {
	if (node->keyNum == 0) {
		node->keyArray[0] = key;
		node->keyNum++;
		return 0;//这个值已存在
	}
	else {
		int i = node->keyNum-1;//从后查找
		while (i >= 0 && node->keyArray[i] > key) {
			node->keyArray[i + 1] = node->keyArray[i];//比当前的大就移位
			i--;
		}
		node->keyArray[i + 1] = key;
		node->keyNum++;
		return (i + 1);
	}
	
}

/*将某个值插入b-树*/
bool BMinusTree::Insert(Type key) {
	SearchResult * result = Search(key);
	TreeNode* node = result->node;
	bool isSearched = result->isSearched;//已经有这个值 插入不成功
	if (isSearched) {
		return false;
	}
	else {
		//node is empty root 空树
		if (node == NULL) {
			node = new TreeNode();
			root = node;
		}

		insertInNode(node, key);//插到node结点
		NodeNum++;
		if (node->keyNum < degree) {
			return true;
		}
		else {
			SplitChild(node);//满了就分裂
		}

	}
}

/*未完成的移除算法*/
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

/*判断某个节点是否是叶节点*/
bool BMinusTree::IsLeaf(TreeNode * node) {
	for (int i = 0; i < childMax;i++) {
		if (node->childArray[i] != NULL) {
			return false;
		}
	}
	return true;
}

/*生成不重复随机数*/
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
			parent = tempNode->parentNode;//让父母的游标记住当前的父母
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
