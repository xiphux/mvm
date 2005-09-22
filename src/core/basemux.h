/*
 * basemux.h
 * Abstract MUX class
 * Copyright (C) 2005 Christopher Han
 */
#ifndef MVM_BASEMUX_H
#define MVM_BASEMUX_H

class basemux
{
public:
	virtual unsigned int getstate() = 0;
};

#endif /* MVM_BASEMUX_H */
