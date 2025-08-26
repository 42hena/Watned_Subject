#pragma comment(lib, "Winmm.lib")
#include "QueueArray.h"
#include "Stack.h"
#include "Command.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>


int keyDown[255];

bool GetKeyDownQ()
{
	return keyDown[(int)'Q'];
}

bool GetKeyDownW()
{
	return keyDown[(int)'W'];
}

bool GetKeyDownE()
{
	return keyDown[(int)'E'];
	
}

bool GetKeyDownR()
{
	return keyDown[(int)'R'];
}
bool GetKeyDownUndo()
{
	return keyDown[VK_OEM_COMMA];
}
bool GetKeyDownRedo()
{
	return keyDown[VK_OEM_PERIOD];
}

bool GetKeyDownShow()
{
	return keyDown[VK_OEM_2];
}

int main()
{
	TQueueArray<Command*> tqa(4096);
	TStackArray<Command*> undoStack(4096);
	TStackArray<Command*> redoStack(4096);

	
	int remainTime = 200;
	DWORD lastTime = timeGetTime();
	while (true)
	{
		for (int i = 0; i < 255; ++i) {
			SHORT result = GetAsyncKeyState(i);
			if (result & 0x8000) {
				keyDown[i] = true;
			}
		}

		if (GetKeyDownQ()) {
			tqa.Push(new QCommand());
		}
		if (GetKeyDownW()) {
			tqa.Push(new WCommand());
		}
		if (GetKeyDownE()) {
			tqa.Push(new ECommand());
		}
		if (GetKeyDownR()) {
			tqa.Push(new RCommand());
		}
		if (GetKeyDownUndo()) {
			tqa.Push(new UndoCommand());
		}
		if (GetKeyDownRedo()) {
			tqa.Push(new RedoCommand());
		}
		if (GetKeyDownShow()) {
			tqa.Push(new ShowCommand());
		}
		/*
		*	Frame 안인경우
		*/
		DWORD checkTime = timeGetTime();
		remainTime -= (checkTime - lastTime);
		lastTime = checkTime;
		if (remainTime < 0)
		{
			std::cout << "큐의 사이즈: " << tqa.Size() << '\n';
			while (tqa.IsEmpty() == false)
			{
				
				Command *command;
				bool result = tqa.Pop(command);
				if (result == false) {
					DebugBreak();
				}
				char type = command->GetType();
				if (type == '<' || type == '>' || type == '?')
				{
					delete command;
					if (type == '<') {
						if (undoStack.Pop(command)) {
							command->Excute();
							redoStack.Push(command);
						}
					}
					else if (type == '>')
					{
						if (redoStack.Pop(command)) {
							command->Excute();
							undoStack.Push(command);
						}
					}
					else if (type == '?')
					{
						for (int i = 0; i < undoStack.Size(); ++i) {
							std::cout << undoStack[i]->GetType() << ' ';
						}
						std::cout << '\n';

						for (int i = 0; i < redoStack.Size(); ++i) {
							std::cout << redoStack[i]->GetType() << ' ';
						}
						std::cout << '\n';
						
					}
				}
				else
				{
					command->Excute();
					undoStack.Push(command);
				}

			}
			remainTime = 200;
		}


		// Clear
		for (int i = 0; i < 255; ++i) {
			keyDown[i] = 0;
		}
		Sleep(10);
	}
}