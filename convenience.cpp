/*
 * convenience.cpp
 * Convenience function implementations
 * Copyright (C) 2005 Christopher Han
 */
#include "convenience.h"

void strip_leading_whitespace(std::string &str)
{
	if (str.size() < 1)
		return;
	char ch = str.at(0);
	while (ch == ' ' || ch == '\t') {
		str.erase(0,1);
		if (str.empty())
			break;
		ch = str.at(0);
	}
}

void strip_trailing_whitespace(std::string &str)
{
	if (str.size() <= 1)
		return;
	std::string::size_type s = str.size()-1;
	char ch = str.at(str.size()-1);
	while (ch == ' ' || ch == '\t') {
		str.erase(s,1);
		if (str.empty())
			break;
		s = str.size()-1;
		ch = str.at(s);
	}
}

void strip_comments(std::string &str)
{
	std::string::size_type i = str.find_first_of('#');
	if (i != std::string::npos)
		str.erase(i);
}

std::vector<std::string> tokenize(std::string &str, const char delim)
{
	std::vector<std::string> params;
	std::string parm;
	char ch;
	while (str.size()>0) {
		ch = str.at(0);
		if (ch != delim)
			parm.push_back(ch);
		else {
			params.push_back(parm);
			parm.clear();
		}
		str.erase(0,1);
	}
	params.push_back(parm);
	return params;
}

void binaryprint(const unsigned int val, const bool zero)
{
	if (!zero && !val)
		return;
	unsigned int mask = 0x80000000;
	for (int i = 0; i < 32; i++) {
		printf("%d",(val&mask?1:0));
		mask >>= 1;
	}
	printf("\n");
}
