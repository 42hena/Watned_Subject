#include "Command.h"
#include "Stack.h"
#include <iostream>

UndoCommand::UndoCommand()
{
}


QCommand::QCommand()
{
}

void QCommand::Excute()
{
	std::cout << "Q가 실행되었습니다\n";	
}
WCommand::WCommand()
{
}

void WCommand::Excute()
{
	std::cout << "W가 실행되었습니다\n";
}
ECommand::ECommand()
{
}

void ECommand::Excute()
{
	std::cout << "E가 실행되었습니다\n";
}
RCommand::RCommand()
{
}

void RCommand::Excute()
{
	std::cout << "E가 실행되었습니다\n";
}


void UndoCommand::Excute()
{
	std::cout << "UndoCommand 실행\n";
}

RedoCommand::RedoCommand()
{
}

void RedoCommand::Excute()
{
	std::cout << "RedoCommand 실행\n";
}


ShowCommand::ShowCommand()
	
{

}

void ShowCommand::Excute()
{
	
}
