#include<iostream>
#include<math.h>//算随机数
#include<time.h>//
#include<stdlib.h>
#include<set>//没有重复项
#include<queue>
#include<string>
using namespace std;

typedef int Type;
#define none -32767/*数组中的初始值*/
static const int degree = 3;/*b树的阶*/
static const int keyMax = degree - 1;/*一个节点包含的最大关键字数量*/
static const int keyMin = (int)ceil(degree / 2.0) - 1;/*一个节点包含的最小关键字数量，ceil向上取整*/
static const int childMax = degree;/*一个节点包含的最大子节点数量*/
static const int childMin = (int)ceil(degree / 2.0);/*一个节点包含的最小子节点数量*/

struct TreeNode
{
	int keyNum;/*实际存在的关键字数量*/
	Type keyArray[degree];/*关键字数组*/
	TreeNode * parentNode;/*父节点*/
	TreeNode * childArray[childMax + 1];/*子节点数组*/
	/*初始化函数*/
	TreeNode(bool isleaf = true, int n = 0) {
		this->keyNum = n;
		this->parentNode = NULL;//空树特判
		for (int i = 0; i < childMax + 1; i++) {
			this->childArray[i] = NULL;
		}
		for (int i = 0; i < degree; i++) {
			this->keyArray[i] = none;
		}
	}
};

struct SearchResult
{
	bool isSearched;/*是否被搜索到*/
	TreeNode * node;/*搜索结束的位置节点，便于插入*/
	/*init*/
	SearchResult(TreeNode* tn = NULL, bool issearched = false) {
		this->node = tn;
		this->isSearched = issearched;
	}
};
