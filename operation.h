/*
 * operation.h
 * Abstract operation class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef OPERATION_H
#define OPERATION_H

class operation
{
public:
	virtual unsigned int instruction() = 0;
};

#endif /* OPERATION_H */
