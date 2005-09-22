/*
 * adder.h
 * Adder class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef MVM_ADDER_H
#define MVM_ADDER_H

class adder
{
public:
	adder();
	~adder();
	void setaval(const int v);
	void setbval(const int v);
	void execute();
	int getresult();
private:
	int a;
	int b;
	int result;
};

#endif /* MVM_ADDER_H */
