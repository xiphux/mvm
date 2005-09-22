/*
 * adder.cpp
 * Adder class implementation
 * Copyright (C) 2005 Christopher Han
 */
#include "adder.h"

adder::adder():a(0),b(0),result(0)
{
}

adder::~adder()
{
}

void adder::setaval(const int v)
{
	a = v;
}

void adder::setbval(const int v)
{
	b = v;
}

void adder::execute()
{
	result = a + b;
}

int adder::getresult()
{
	return result;
}
