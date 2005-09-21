/*
 * convenience.h
 * Convenience function definitions
 * Copyright (C) 2005 Christopher Han
 */
#ifndef CONVENIENCE_H
#define CONVENIENCE_H

#include <string>
#include <vector>

void strip_leading_whitespace(std::string &str);
void strip_trailing_whitespace(std::string &str);
void strip_comments(std::string &str);
std::vector<std::string> tokenize(std::string &str, const char delim);
void binaryprint(const unsigned int val, const bool zero = true);

#endif /* CONVENIENCE_H */
