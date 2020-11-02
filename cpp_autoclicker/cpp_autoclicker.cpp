#include <iostream>
#include <windows.h>

void PrintSplash() {
	std::cout << "----------------\n";
	std::cout << "AUTOCLICKER v0.1\n";
	std::cout << "----------------\n";
}

void GetMethodNumber(int& method) {
	std::cout << "0) Exit\n";
	std::cout << "1) Position\n";
	std::cout << "2) Right\n";
	std::cout << "3) Left\n";
	std::cout << "4) Move to\n";
	std::cout << "Enter number:\n> ";
	std::cin >> method;
}

void GetMousePosition(int& xPos, int& yPos) {
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	xPos = mousePosition.x;
	yPos = mousePosition.y;
}

void MouseRightClick() {
	// Create input object
	INPUT Input = { 0 };

	// Set input type
	Input.type = INPUT_MOUSE;
	// Simulate click down
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	// Send input
	::SendInput(1, &Input, sizeof(Input));

	// Clear object
	::ZeroMemory(&Input, sizeof(Input));
	// Set input type
	Input.type = INPUT_MOUSE;
	// Simulate click up
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	// Send input
	::SendInput(1, &Input, sizeof(Input));
}

void MouseLeftClick() {
	// Create input object
	INPUT Input = { 0 };

	// Left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(Input));

	// Left up
	::ZeroMemory(&Input, sizeof(Input));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(Input));
}

void MouseMoveTo(int toX, int toY) {
	// Get screen size (x and y) in pointer coordinates format
	double x = ::GetSystemMetrics(SM_CXSCREEN);
	double y = ::GetSystemMetrics(SM_CYSCREEN);

	// Get location: toX*(65535.0f/x)
	double dx = toX * (65535.0f / x);
	double dy = toY * (65535.0f / y);

	// Create input with type, "pipe" move and variety flags and assign locations
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = LONG(dx);
	Input.mi.dy = LONG(dy);
	// Send input
	::SendInput(1, &Input, sizeof(Input));
}

void CustomizeClicker(const char* type, int& numOfClicks, int& sleepTime) {
	std::cout << "Number of " << type << ": ";
	std::cin >> numOfClicks;
	std::cout << "Wait between " << type << " (ms): ";
	std::cin >> sleepTime;
}

void CountDown() {
	std::cout << "Starting in 3 seconds...\n";
	Sleep(1000);
	std::cout << "2..\n";
	Sleep(1000);
	std::cout << "1..\n";
	Sleep(1000);
}

int main()
{
	// Title
	SetConsoleTitle(L"AutoClicker v0.1");

	// Set up variables
	int xPos, yPos;
	int methodNumber = 0;
	int numOfClicks = 0;
	int sleepTime = 0;

start:
	PrintSplash();
	GetMethodNumber(methodNumber);

	if (methodNumber == 1) {
		CustomizeClicker("reads", numOfClicks, sleepTime); CountDown();
		for (int i = 0; i < numOfClicks; i++) {
			GetMousePosition(xPos, yPos);
			CountDown();
			printf("X, Y: (%i, %i)\n", xPos, yPos);
			Sleep(sleepTime);
		}
		goto start;
	}
	else if (methodNumber == 2) {
		CustomizeClicker("clicks", numOfClicks, sleepTime); CountDown();
		for (int i = 0; i < numOfClicks; i++) {
			MouseRightClick();
			Sleep(sleepTime);
		}
		goto start;
	}
	else if (methodNumber == 3) {
		CustomizeClicker("clicks", numOfClicks, sleepTime); CountDown();
		for (int i = 0; i < numOfClicks; i++) {
			MouseLeftClick();
			Sleep(sleepTime);
		}
		goto start;
	}
	else if (methodNumber == 4) {
		CustomizeClicker("moves", numOfClicks, sleepTime);
		std::cout << "Enter X position: ";
		std::cin >> xPos;
		std::cout << "Enter Y position: ";
		std::cin >> yPos;
		CountDown();
		for (int i = 0; i < numOfClicks; i++) {
			MouseMoveTo(xPos, yPos);
			Sleep(sleepTime);
		}
		goto start;
	}
	else {
		return 0;
	}
}