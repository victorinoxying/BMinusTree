#include<iostream>
#include<math.h>//�������
#include<time.h>//
#include<stdlib.h>
#include<set>//û���ظ���
#include<queue>
#include<string>
using namespace std;

typedef int Type;
#define none -32767/*�����еĳ�ʼֵ*/
static const int degree = 3;/*b���Ľ�*/
static const int keyMax = degree - 1;/*һ���ڵ���������ؼ�������*/
static const int keyMin = (int)ceil(degree / 2.0) - 1;/*һ���ڵ��������С�ؼ���������ceil����ȡ��*/
static const int childMax = degree;/*һ���ڵ����������ӽڵ�����*/
static const int childMin = (int)ceil(degree / 2.0);/*һ���ڵ��������С�ӽڵ�����*/

struct TreeNode
{
	int keyNum;/*ʵ�ʴ��ڵĹؼ�������*/
	Type keyArray[degree];/*�ؼ�������*/
	TreeNode * parentNode;/*���ڵ�*/
	TreeNode * childArray[childMax + 1];/*�ӽڵ�����*/
	/*��ʼ������*/
	TreeNode(bool isleaf = true, int n = 0) {
		this->keyNum = n;
		this->parentNode = NULL;//��������
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
	bool isSearched;/*�Ƿ�������*/
	TreeNode * node;/*����������λ�ýڵ㣬���ڲ���*/
	/*init*/
	SearchResult(TreeNode* tn = NULL, bool issearched = false) {
		this->node = tn;
		this->isSearched = issearched;
	}
};
