
#include<unordered_map>
#include<vector>
#include<iostream>
#include<queue>
#include<string>
using namespace std;
class TreeNode {
public:
	char data;
	int freq;
	TreeNode* left;
	TreeNode* right;
	TreeNode(char data,int freq) {
		this->data = data;
		this->freq = freq;
		this->left = NULL;
		this->right = NULL;
	}
	TreeNode(char data, int freq, TreeNode* right, TreeNode* left) {
		this->data=data;
		this->freq=freq;
		this->left = left;
		this->right = right;
	}
};
class Compare {
public:
	bool operator()(TreeNode*a,TreeNode*b) {
		return a->freq > b->freq;
	}
};
unordered_map<char, string>newbits;
class Tree {
public:
	TreeNode* root;
	Tree() {
		root = NULL;
	}
private:
	void printtree(TreeNode *root,string s) {
		if (root == NULL) {
			return;
		}
		if (root->data != NULL) {
			newbits[root->data] = s;
		}
		printtree(root->left, s + '0');
		printtree(root->right, s + '1');
	}
public:
	void printtree() {
		string s = "";
		printtree(root,s);
	}
};
int main() {
	cout << "enter the string you want to enter (spaces are allowed) to compress :" << endl;
	//taking input string
	string theinputstring;
	//cin >> theinputstring;
	getline(cin, theinputstring);
	cout << endl;
	
	//making hashmap for counting the frequency of each element in the string 

	unordered_map<char, int>thefrequencycounter;
	for (int i = 0; i < theinputstring.size(); i++) {
		if (thefrequencycounter.find(theinputstring[i]) == thefrequencycounter.end()) {
			thefrequencycounter[theinputstring[i]] = 1;
		}
		else {
			thefrequencycounter[theinputstring[i]]++;
		}
	}
	//initializing minheap
	priority_queue<TreeNode*,vector<TreeNode*>,Compare>minheap;
	for (auto itr = thefrequencycounter.begin(); itr != thefrequencycounter.end(); itr++) {
		TreeNode* basicnodes=new TreeNode(itr->first,itr->second);
		minheap.push(basicnodes);
	}
	//making a tree of character from bottom to up
	while (minheap.size()!=1) {
		TreeNode* first = minheap.top();
		minheap.pop();
		TreeNode* second = minheap.top();
		minheap.pop();
		TreeNode* sumnode = new TreeNode(NULL,first->freq+second->freq,first,second);
		minheap.push(sumnode);
	}
	//initalizing tree data type
	Tree* base=new Tree;
	base->root = minheap.top();
	//calling function to make new bits(data compression)
	base->printtree();
	//stored new bits int the hashmap
	for (auto itr = newbits.begin(); itr != newbits.end(); itr++) {
		cout << itr->first << " " << itr->second<<endl;
	}
	cout << endl << endl;
	//making the binary string
	cout << "the binary string made using our new bits :" << endl;
	string outputstring="";
	for (int i = 0; i < theinputstring.size(); i++) {
		outputstring += newbits[theinputstring[i]];
	}
	cout << outputstring<<endl;
	cout << endl;
	//storing the reverse of the hashmap new bits
	unordered_map<string, char>reverser;
	for (auto itr = newbits.begin(); itr != newbits.end(); itr++) {
		reverser[itr->second] = itr->first;
	}
	string ans="",temp="";
	//decoding the string
	for (int i = 0; i < outputstring.size(); i++) {
		temp += outputstring[i];
		if (reverser.find(temp) != reverser.end()) {
			ans += reverser[temp];
			temp = "";
		}
	}

	cout << "the string verification at another end" << endl;
	cout << ans << endl;
	cout << endl << endl;
	cout << "your string takes " << theinputstring.size()*8<<" bits of memory"<<endl;
	cout << "but the compressed string takes " << outputstring.size()<<" bits of memory"<<endl;
	cout << "memory saved by you is " << theinputstring.size() * 8 - outputstring.size() << " bits which is about ";
	cout<< ((theinputstring.size() * 8.0 - outputstring.size())/(theinputstring.size()*8.0))*100 << " percent" << endl;
