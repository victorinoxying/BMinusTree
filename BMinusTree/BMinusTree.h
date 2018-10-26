#include"Global.h"

class BMinusTree
{
private:

	TreeNode * root;/*根节点*/
	int NodeNum;/*所有关键字数量*/

protected:
	SearchResult* search(TreeNode* &Node, Type key);/*查找功能封装*/
	void SplitChild(TreeNode* childNode);/*节点分裂功能封装*/
	int insertInNode(TreeNode* &node, Type key);/*key插入功能封装*/

public:
	BMinusTree();
	~BMinusTree();
	bool Insert(Type key);/*插入函数*/
	SearchResult* Search(Type key);/*搜索函数*/
	bool Remove(Type key);/*删除函数*/
	bool IsLeaf(TreeNode*node);/*判断某个节点是不是叶子节点*/ //没啥用。。
	set<Type> getRandomNum(int num);/*返回n个不重复随机数0-max_rand*/
	void Output();/*层次遍历树，并打印*/
};

