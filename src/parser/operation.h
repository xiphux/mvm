/*
 * operation.h
 * Abstract operation class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef MVM_OPERATION_H
#define MVM_OPERATION_H

class operation
{
public:
	virtual unsigned int instruction() = 0;
};

#endif /* MVM_OPERATION_H */
