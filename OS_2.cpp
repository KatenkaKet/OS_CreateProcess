#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

//typedef struct _STARTUPINFO
//{
//	DWORD cb;				// Размер структуры
//	LPTSTR lpReserved;		// Зарезервировано
//	LPTSTR lpDesktop;		// Указатель на строку рабочего стола и/или
//	LPTSTR lpTitle;			// Указатель на строку заголовка окна
//	DWORD dwX;				// Координата по горизонтали левого верхнего угла окна
//	DWORD dwY;				// Координата по вертикали левого верхнего угла окна
//	DWORD dwXSize;			// Ширина окна
//	DWORD dwYSize;			// Высота окна
//	DWORD dwXCountChars;	// Ширина буфера окна в символах
//	DWORD dwYCountChars;	// Высота буфера окна в символах
//	DWORD dwFillAttribute;	// Цвет шрифта, фона
//	DWORD dwFlags;			// Управляющие флаги
//	WORD wShowWindow;		// Способ отображения окна
//	WORD cbReserved2;		// Зарезервировано
//	LPBYTE lpReserved2;		// Зарезервировано
//	HANDLE hStdInput;		// Дескриптор стандартного потока ввода
//	HANDLE hStdOutput;		// Дескриптор стандартного потока вывода
//	HANDLE hStdError;		// Дескриптор стандартного потока вывода ошибок
//} STARTUPINFO;

//typedef struct _PROCESS_INFORMATION
//{
//	HANDLE hProcess;		// Дескриптор процесса
//	HANDLE hThread;			// Дескриптор потока
//	DWORD dwProcessId;		// Идентификатор процесса
//	DWORD dwThreadId;		// Идентификатор потока
//} PROCESS_INFORMATION;

int main() {

	LPCWSTR path = L"C:\\Windows\\System32\\notepad.exe"; // путь к вызову "notepad.exe"
	STARTUPINFO SI;										
	PROCESS_INFORMATION PI;								
	ZeroMemory(&SI, sizeof(SI));						  // Заполнение структуры SI нулями
	SI.cb = sizeof(SI);									
	ZeroMemory(&PI, sizeof(PI));						  // Заполнение структуры PI нулями
	// Создание процесса
	if (!CreateProcess(path, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &SI, &PI)) {
		cout << "CreateProcess faild. Error: " << GetLastError() << endl;
		return 1;
	}
	WaitForSingleObject(PI.hProcess, INFINITE); // Ожидание завершения создания процесса
	
	//	Определение дескриптора созданного процесса по идентификатору:
	cout << "Handle Process by id: " << GetProcessId(PI.hProcess) << endl;
	cout << "Process id: " << PI.dwProcessId << endl;
	cout << "Thread id: " << PI.dwThreadId << endl;
	cout << "Current Process ID: " << GetCurrentProcessId() << endl;
	cout << "Current Thread ID: " << GetCurrentThreadId() << endl;
	// Проверка уникальности дескрипторов процессов;
	cout << "Handle Process: " << GetCurrentProcess() << endl;
	cout << "Handle Thread: " << GetCurrentThread() << endl;
	if (GetCurrentProcess() == PI.hProcess) {
		cout << "Process descriptors are not uniqu." << endl;
	}
	else {
		cout << "Process descriptors are uniqu." << endl;
	}
	// Получение значений временных характеристик процессов;
	FILETIME CreationTime, ExitTime, KernelTime, UserTime;
	if (GetProcessTimes(PI.hProcess, &CreationTime, &ExitTime, &KernelTime, &UserTime)) {
		SYSTEMTIME SystemTime, SystemTime1, SystemTime2;
		if (FileTimeToSystemTime(&CreationTime, &SystemTime)) {
			cout << "Created date: " << SystemTime.wYear << '.' << SystemTime.wMonth << '.' << SystemTime.wDay << endl;
			cout << "Created time: " << SystemTime.wHour << ':' << SystemTime.wMinute << ':' << SystemTime.wSecond << endl;
		}
		else {
			cout << "Not information. Error: " << GetLastError() << endl;
		}
		if (FileTimeToSystemTime(&KernelTime, &SystemTime1)) {
			cout << "KernelTime date: " << SystemTime1.wYear << '.' << SystemTime1.wMonth << '.' << SystemTime1.wDay << endl;
			cout << "KernelTime time: " << SystemTime1.wHour << ':' << SystemTime1.wMinute << ':' << SystemTime1.wSecond << endl;
			cout << "KernelTime time: " << SystemTime1.wHour << ':' << SystemTime1.wMinute << ':' << SystemTime1.wSecond << ':' << SystemTime1.wMilliseconds << endl;
		}
		else {
			cout << "Not information. Error: " << GetLastError() << endl;
		}
		if (FileTimeToSystemTime(&UserTime, &SystemTime2)) {
			cout << "UserTime date: " << SystemTime2.wYear << '.' << SystemTime2.wMonth << '.' << SystemTime2.wDay << endl;
			cout << "UserTime time: " << SystemTime2.wHour << ':' << SystemTime2.wMinute << ':' << SystemTime2.wSecond << ':' << SystemTime2.wMilliseconds << endl;
		}
		else {
			cout << "Not information. Error: " << GetLastError() << endl;
		}
	}
	else {
		cout << "GetProcessTimes faild. Error: " << GetLastError() << endl;
		return 1;
	}
	// Завершение процесса и закрытие открытых ранее дескрипторов;
	CloseHandle(PI.hProcess);	// Закрытие дискриптора процесса
	CloseHandle(PI.hThread);	// Закрытие дискриптора потока

	cout << "Process created successful" << endl;

	return 0;
}
