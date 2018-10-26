#include"Global.h"

class BMinusTree
{
private:

	TreeNode * root;/*���ڵ�*/
	int NodeNum;/*���йؼ�������*/

protected:
	SearchResult* search(TreeNode* &Node, Type key);/*���ҹ��ܷ�װ*/
	void SplitChild(TreeNode* childNode);/*�ڵ���ѹ��ܷ�װ*/
	int insertInNode(TreeNode* &node, Type key);/*key���빦�ܷ�װ*/

public:
	BMinusTree();
	~BMinusTree();
	bool Insert(Type key);/*���뺯��*/
	SearchResult* Search(Type key);/*��������*/
	bool Remove(Type key);/*ɾ������*/
	bool IsLeaf(TreeNode*node);/*�ж�ĳ���ڵ��ǲ���Ҷ�ӽڵ�*/ //ûɶ�á���
	set<Type> getRandomNum(int num);/*����n�����ظ������0-max_rand*/
	void Output();/*��α�����������ӡ*/
};

