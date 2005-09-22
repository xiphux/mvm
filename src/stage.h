/*
 * stage.h
 * Abstract stage class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef MVM_STAGE_H
#define MVM_STAGE_H

class stage
{
public:
	virtual void tick() = 0;
};

#endif /* MVM_STAGE_H */
