/*
 * mux2.h
 * 2-Way MUX class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef MVM_MUX2_H
#define MVM_MUX2_H

#include "basemux.h"

class mux2: public basemux
{
public:
	mux2();
	~mux2();
	unsigned int getstate();
	void setstate(const unsigned int st);
	void setstate(const bool st);
private:
	bool state;
};

#endif /* MVM_MUX2_H */
