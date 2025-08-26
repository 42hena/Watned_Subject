#pragma once

template<typename T>
class TStackArray;
class Command
{
public:
	virtual void Excute() = 0;
	virtual char GetType() { return 0; }
};

class QCommand : public Command
{
public:
	QCommand();
	virtual void Excute();
	virtual char GetType()
	{
		return 'Q';
	}
};
class WCommand : public Command
{
public:
	WCommand();
	virtual void Excute();
	virtual char GetType()
	{
		return 'W';
	}
};
class ECommand : public Command
{
public:
	ECommand();
	virtual void Excute();
	virtual char GetType()
	{
		return 'E';
	}
};
class RCommand : public Command
{
public:
	RCommand();
	virtual void Excute();
	virtual char GetType()
	{
		return 'R';
	}
};

class UndoCommand: public Command
{
public:
	UndoCommand();
	virtual void Excute() override;
	virtual char GetType()
	{
		return '<';
	}

};

class RedoCommand : public Command
{
public:
	RedoCommand();
	virtual void Excute() override;
	virtual char GetType()
	{
		return '>';
	}

};

class ShowCommand : public Command
{
public:
	ShowCommand();
	virtual void Excute() override;
	virtual char GetType()
	{
		return '?';
	}
};