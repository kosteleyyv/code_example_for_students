// Threads.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <locale>

//#define REALIZE_LOGIC_1

#ifdef REALIZE_LOGIC_1

bool isEnd = false;
int i = 0;

HANDLE hThread = NULL;
unsigned long uThreadID = 0;

void WorkFunc()
{
	while (!isEnd)
	{
		i++;
	}
}
int main()
{
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkFunc, NULL, 0, &uThreadID);

	while (!isEnd)
	{
		int codeKey = 0;
		std::cin >> codeKey;

		switch (codeKey)
		{
		case 0: isEnd = true; break;
		case 1: std::cout << std::endl << " i=" << i << std::endl; break;
		}
	}

	std::cout << i;
	CloseHandle(hThread);
}
#endif

//#define UN_REALIZE_LOGIC_1

#ifdef UN_REALIZE_LOGIC_1

int main()
{
	bool isEnd = false;	
	int i = 0;

	while (!isEnd)//условие выхода
	{
		i++;//какое-то математическая задача

		int codeKey = 0;
		std::cin >> codeKey;//пользовательская команда

		switch (codeKey)
		{
		case 0: isEnd = true; break;//завершение
		case 1: std::cout << std::endl << " i=" << i << std::endl; break;//вывод на экран
		}
		
	}

	std::cout << i;	
}

#endif // REALIZE_LOGIC


//#define WRONG_REALIZE_LOGIC_2

#ifdef WRONG_REALIZE_LOGIC_2

#define ARRAY_COUNT 5
int _array[ARRAY_COUNT];

HANDLE hThread = NULL;
unsigned long uThreadID = 0;

void Thread(void* pParams)
{
	int i, tickCounter = 1;
	Sleep(1);

	while (tickCounter < 1000)
	{
		for (i = 0; i < ARRAY_COUNT; ++i)
		{
			_array[i] = tickCounter;
		}

		++tickCounter;
		Sleep(1);
	}
}

int main(void)
{
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, &uThreadID);

	int tickCounter = 0;

	while (tickCounter++ < 20)
	{
		for (int i = 0; i < ARRAY_COUNT; ++i)
		{
			printf("%d ", _array[i]);
		}
		printf(" i=%i \n", tickCounter);
	}

	CloseHandle(hThread);
	return 0;
}


#endif


//#define REALIZE_LOGIC_2

#ifdef REALIZE_LOGIC_2


#define ARRAY_COUNT 5

LPCWSTR _title = L"My Mutex";

struct SWT
{
	int array[ARRAY_COUNT];
	int tickCounterThread = 0;
	int tickCounterMain = 0;
};

HANDLE hThread = NULL;
unsigned long uThreadID = 0;


void Thread(void* pParams)
{
	SWT* data=(SWT*)pParams;

	HANDLE hMutex = CreateMutex(NULL, FALSE, _title);
	int i;
	Sleep(1);

	while (data->tickCounterThread < 100)
	{
		WaitForSingleObject(hMutex, INFINITE);

		printf("Забрал Thread  -");
		for (i = 0; i < ARRAY_COUNT; ++i)
		{
			data->array[i] = data->tickCounterThread;
		}
		++data->tickCounterThread;
		printf("- Освободил Thread\n");
		ReleaseMutex(hMutex);
		Sleep(1);
	}
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	
	SWT data;

	HANDLE hMutex = CreateMutex(NULL, FALSE, _title);
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)&data, 0, &uThreadID);

	while (data.tickCounterMain++ < 20)
	{
		WaitForSingleObject(hMutex, INFINITE);
		printf("Забрал main - ");
		for (int i = 0; i < ARRAY_COUNT; ++i)
		{
			printf("%d ", data.array[i]);
		}
		printf("- Освободил main\n");
		ReleaseMutex(hMutex);
	}

	WaitForSingleObject(hMutex, INFINITE);
	printf("Забрал main - ");
	printf("логика в main завершилась, когда Thread на %d итерации", data.tickCounterThread);
	printf("- Освободил main\n");
	ReleaseMutex(hMutex);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hMutex);

	printf("Завершение\n");

	return 0;
}
#endif



#define REALIZE_LOGIC_3

#ifdef REALIZE_LOGIC_3
struct SWT//разделяемые данные
{
	HANDLE hevBeg;//событие запуска работы рабочего потока
	HANDLE hevEnd;//событие завершения работы рабочего потока
	CRITICAL_SECTION cs;//критическа секция для модификации counter
	INT counter = 0;//модифициремые из двух потоков данные
};

DWORD WINAPI ThreadFunc(LPVOID pData)
{
	printf("%lu ms::Рабочий поток: Попали в рабочий поток\r\n", clock());
	SWT* pswt = (SWT*)pData;

	printf("%lu ms::Рабочий поток: Уходим в ожидание запуска\r\n", clock());
	WaitForSingleObject(pswt->hevBeg, INFINITE);

	printf("%lu ms::Рабочий поток: Нас запустили. Ожидание конец действий\r\n", clock());

	while (WaitForSingleObject(pswt->hevEnd, 0) != WAIT_OBJECT_0)
	{
		EnterCriticalSection(&pswt->cs);

		pswt->counter++;

		unsigned long startSleep = clock();
		Sleep(2);
		unsigned long stopSleep = clock();

		printf("%lu ms::Рабочий поток: Выполняем итерацию %i, время выполнения Sleep(2) = %lu мс\r\n", clock(), pswt->counter, (stopSleep - startSleep));		

		LeaveCriticalSection(&pswt->cs);
	}

	printf("%lu ms::Рабочий поток: Поспим, чтобы показать, как главный нас ждет\r\n", clock());
	Sleep(100);
	printf("%lu ms::Рабочий поток: Завершили действия, снимем событие\r\n", clock());
	ResetEvent(pswt->hevEnd);

	printf("%lu ms::Рабочий поток: Выход\r\n", clock());
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	HANDLE hThread;
	DWORD idThread;
	SWT params;

	params.hevBeg = CreateEvent(NULL, TRUE, FALSE, NULL);
	params.hevEnd = CreateEvent(NULL, TRUE, FALSE, NULL);

	InitializeCriticalSection(&params.cs);

	hThread = CreateThread(NULL, 0, ThreadFunc, &params, 0, &idThread);

	if (!hThread)
	{
		return -1;
	}

	printf("%lu ms::Главный поток: Все подготовили. Чуть-чуть поспим\r\n", clock());
	Sleep(500);

	printf("%lu ms::Главный поток: Подаем сигнал к старту\r\n", clock());
	SetEvent(params.hevBeg);

	printf("%lu ms::Главный поток: Еще заснули\r\n", clock());
	Sleep(100);

	EnterCriticalSection(&params.cs);
	params.counter = -1;
	printf("%lu ms::Главный поток: Проведем модификацию данных на значение %i\r\n", clock(), params.counter);
	LeaveCriticalSection(&params.cs);

	printf("%lu ms::Главный поток: Еще заснули\r\n", clock());
	Sleep(100);

	printf("%lu ms::Главный поток: Подаем сигнал к завершению\r\n", clock());

	SetEvent(params.hevEnd);

	printf("%lu ms::Главный поток: Ожидаем завершение\r\n", clock());

	while (WaitForSingleObject(params.hevEnd, 200) == WAIT_OBJECT_0)
	{
		printf("%lu ms::Главный поток: Рабочий поток еще не завершился\r\n", clock());
		Sleep(10);
	}
	printf("%lu ms::Главный поток: Дождались завершения, все очищаем\r\n", clock());
	CloseHandle(hThread);
	CloseHandle(params.hevBeg);
	CloseHandle(params.hevEnd);
	DeleteCriticalSection(&params.cs);

	getchar();
	return 0;
}
#endif