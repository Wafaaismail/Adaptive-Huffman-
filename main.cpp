// test1.cpp : Defines the entry point for the console application.
//
// encode with root (myt) all functions must be called with this root after init(myt)
// decode with root (d) 

//add function returns the NYT parent node and take NYT node as a parameter to add after it 

#include "stdafx.h"
#include <queue>
#include <iostream>
#include <string>
#include<conio.h>
#include <bitset>
#include <set>
using namespace std;

struct Tree
{
	int weight;
	int number;
	char c;
	char path;
	Tree* parent;
	Tree* left;
	Tree* right;
};

//var 
Tree* myt = new Tree;
Tree* tmp = new Tree; // NYT node


Tree *d = new Tree;
Tree* tmpd = new Tree; // NYT node


vector <char> symbols;
set <char> in;
int e, r;
string encoded="";
char NYT = '\0';
bool first = true;
bool firstdecode = true;
string original = "";

//functions

Tree* search(Tree * t, char c);
string charPath(Tree *t, char c);
Tree* add(Tree* t, char c, Tree* root);
bool checkWeight(Tree* t);
void shuffle(Tree * t);
void initTree(Tree* t);
void inOrder(Tree* t);
void edit_path(Tree* t);
void setParameter();
string tobinary(int size, int num);
int  todecimal(string s);
string getFixedCode(char c);
void encode(string message);
bool check_r(int s);
void decode(string decoded);


int main()
{

	char temp,status;
	do {
		cout << "------------------------------------------------------------------------------" << endl << "Press e to encode || d to decode : " << endl;
		cin >> status;
	} while (status != 'e'&&status != 'd');
	int noOfchar;
	cout << "Enter no. of symbols : " << endl; 
	cin >> noOfchar;
	cout << "Enter symbols : " << endl; 
	for (int i = 0; i < noOfchar; i++)
	{
		cin >> temp; 
		symbols.push_back(temp);	
	}
	string message;
	cout << "Enter message : " << endl;
	cin >> message;
	if (status == 'e')
	{
		initTree(myt);
		encode(message);
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "The encoded message :";
		cout << encoded << endl;
		cout << "The tree in inorder sequence : " << endl;
		inOrder(myt);
	}
	else
	{
		initTree(d);
		decode(message);
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "The decoded message :";
		cout << original << endl;
		cout << "The tree in inorder sequence : " << endl;
		inOrder(d);
	}
	cout << "------------------------------------------------------------------------------" << endl;
	system("PAUSE");
	return 0;
}
Tree* search(Tree * t, char c)
{
	if (t->c == c)
		return t;
	if (t->right == NULL && t->left == NULL)
		return 0;
	else {
		Tree * right = search(t->right, c);
		Tree * left = search(t->left, c);
		if (right != 0) return right;
		if (left != 0) return left;
		return 0;

	}
}
string charPath(Tree *t, char c)
{
	Tree *node = search(t, c);
	string s;
	while (node->parent != NULL)
	{
		s = node->path + s;
		node = node->parent;
	}
	return s;

}
Tree* add(Tree* t, char c, Tree* root)
{
	in.insert(c);
	Tree * tt = search(root, c);
	if (tt&&tt->c == c)
	{

		while (tt)
		{
			tt->weight++;
			tt = tt->parent;
		}
		return t;
	}
	else if (t)
	{
		if (t->c == NYT)
		{

			if (t->right == 0)
			{
				t->right = new Tree;

				t->right->left = 0;
				t->right->right = 0;
				t->right->path = '1';
				t->right->parent = t;

				t->right->c = c;
				t->right->weight = 0;
			}

			if (t->left == 0)
			{
				t->left = new Tree;

				t->left->left = 0;
				t->left->right = 0;
				t->right->path = '0';
				t->left->parent = t;
				t->left->c = NYT;
				t->left->weight = 0;

			}
			t->c = '|';
			Tree* temp = t->right;

			temp->weight++;
			temp = temp->parent;
			while (temp)
			{
				temp->weight++;
				if (temp->parent) temp->path = '0';
				temp = temp->parent;
			}
			return t->left;
		}
	}
}
bool checkWeight(Tree* t)
{
	if (t->left->weight > t->right->weight) return 1; //shuffle 
	else return 0; // do nothing 
}
void shuffle(Tree * t)
{
	if (t->right && t->left)
	{
		if (checkWeight(t))
		{
			Tree* right = t->right;
			Tree* left = t->left;
			t->right = left;
			t->left = right;
			t->right->path = '1';
			t->left->path = '0';
		}
		shuffle(t->right);
		shuffle(t->left);
	}
	return;
}
void initTree(Tree* t)
{
	t->weight = 0;
	t->number = 256;
	t->c = NYT;
	t->parent = 0;
	t->left = 0;
	t->right = 0;
	t->path = '@';
}
void inOrder(Tree* t)
{
	if (t->left)
		inOrder(t->left);
	if (t->c == NYT) t->path = '0';
	cout << "w: " << t->weight << "| path : " << t->path << " | c: " << t->c << endl;;

	if (t->right)
		inOrder(t->right);
}
void edit_path(Tree* t)
{
	if (t->right)
	{
		t->right->path = '1';
		edit_path(t->right);
	}
	if (t->left)
	{
		t->left->path = '0';
		edit_path(t->left);
	}

}
void setParameter()
{
	e = log2((long long)symbols.size());
	r = (long long)symbols.size() - pow(2, e);
}
string tobinary(int size, int num)
{
	string s = "";
	char rr;
	int temp = num, r;
	for (int i = 0; i < size; i++)
	{
		temp = num / 2;
		r = num % 2;
		if (r == 0) rr = '0';
		else rr = '1';
		s = rr + s;
		num /= 2;
	}
	return s;
}
int  todecimal(string s)
{
	int out = 0;
	int temp;
	reverse(s.begin(), s.end());
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '0') temp = 0;
		else temp = 1;
		out += temp * pow(2, i);

	}
	return out;

}
string getFixedCode(char c)
{
	int k;

	for (int i = 0; i < (int)symbols.size(); i++)
	{
		if (symbols[i] == c) {
			k = i + 1;
			break;
		}
	}
	if (k >= 0 && k <= 2 * r)
		return tobinary(e + 1, k - 1);
	else
		return tobinary(e, k - r - 1);
}
void encode(string message)
{
	char temp;
	setParameter();
	for (int i = 0; i < message.size(); i++)
	{
		if (in.find(message[i]) == in.end()) //not found
		{
			encoded += charPath(myt, NYT) + getFixedCode(message[i]);
			if (first) {
				tmp = add(myt, message[i], myt);
				shuffle(myt);
				edit_path(myt);
				first = 0;
			}
			else
			{
				tmp = add(tmp, message[i], myt);
				shuffle(myt);
				edit_path(myt);
			}
		}
		else
		{
			encoded += charPath(myt, message[i]);
			tmp = add(tmp, message[i], myt);
			shuffle(myt);
			edit_path(myt);
		}
	}
}
bool check_r(int s)
{
	if (s < r) return true; // add more bit 
	else return false;
}
void decode(string decoded)
{
	setParameter();
	string temp = "";
	int tempdec;
	int index = 0;
	while (index < decoded.length())
	{
		if (firstdecode)
		{
			for (int i = 0; i < e; i++)
			{
				temp += decoded[i];
				//index = i;
			}
			index += e;
			tempdec = todecimal(temp);
			if (check_r(tempdec))
			{
				temp += decoded[index];
				index++;
				tempdec = todecimal(temp);
			}
			else
			{
				tempdec += r;
			}
			original += symbols[tempdec];
			tmpd = add(d, symbols[tempdec], d);
			shuffle(d);
			edit_path(d);
			firstdecode = 0;
			//index++;
		}
		else {
			Tree *node = new Tree;
			node = d;
			char c;
			while (node->right && node->left)
			{
				c = decoded[index];
				index++;
				if (c == '0')
					node = node->left;
				else
					node = node->right;
			}
			if (node->c != NYT)
			{
				original += node->c;
				tmpd = add(tmpd, node->c, d);
				shuffle(d);
				edit_path(d);
			}
			else
			{
				temp = "";
				tempdec = 0;
				int q = index;
				for (int i = q; i < q + e; i++)
				{
					temp += decoded[i];
					//index ++;
				}
				index += e;
				tempdec = todecimal(temp);
				if (check_r(tempdec))
				{
					temp += decoded[index];
					index++;
					tempdec = todecimal(temp);
					tempdec;
				}
				else
				{
					tempdec += r;
				}
				original += symbols[tempdec];
				tmpd = add(tmpd, symbols[tempdec], d);
				shuffle(d);
				edit_path(d);
				firstdecode = 0;
			}
		}
	}
}
