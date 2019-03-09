#include "StringUtil.hpp" 
#include <iostream>
#include <vector>

using namespace std;;

int main()
{
	StringUtil stringUtil;
	string s = "hello   world";
	vector<string> v;
	
	stringUtil.strSplit(s, v, " ");
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
}
