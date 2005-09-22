/*
 * mux2.cpp
 * 2-Way MUX class implementation
 * Copyright (C) 2005 Christopher Han
 */
#include "mux2.h"

mux2::mux2()
{
	state = false;
}

mux2::~mux()
{
}

unsigned int mux2::getstate()
{
	return (state?1:0);
}

void mux2::setstate(const unsigned int st)
{
	state = (st?true:false);
}

void mux2::setstate(const bool st)
{
	state = st;
}
