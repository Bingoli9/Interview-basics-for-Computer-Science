#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>


class StringUtil
{
	
public:
	StringUtil() = default;
	~StringUtil() = default;
	
	void strSplit(const std::string& s, std::vector<std::string>& v, const std::string& sep)
	{
		std::string::size_type pos1, pos2;
		pos2 = s.find(sep);
		pos1 = 0;
		while(std::string::npos != pos2)
		{
			if (pos2 != pos1) {
				v.push_back(s.substr(pos1, pos2-pos1));	
			}
			
			pos1 = pos2 + sep.size();
			pos2 = s.find(sep, pos1);
		}
		if (pos1 !=s.length()) {
			v.push_back(s.substr(pos1));
		}
	}
	
	void strSplit(char* s, std::vector<std::string>& v, const char* sep)
	{
		char *p;
		p = strtok(s, sep);
		while(p) {
			v.push_back(p);
			p = strtok(NULL, sep);
		}
	}
};
