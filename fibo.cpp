#include <iostream>
#include <thread>
#include <vector>

static std::vector<int> fib_sequence;

void fibonacci(int n = 0)
{
	std::cout << "Started Thread: " << std::this_thread::get_id() << std::endl;

	fib_sequence.push_back(0);
	if (n == 0) return;

	fib_sequence.push_back(1);
	if (n == 1) return;

	int fib = -1;
	for (int i = 2; i <= n; i++)
	{
		fib = fib_sequence[i - 1] + fib_sequence[i - 2];
		fib_sequence.push_back(fib);
	}

	std::cout << "Exiting Thread: " << std::this_thread::get_id() << std::endl;
}

int main()
{
	std::cout << "Main Thread: " << std::this_thread::get_id() << std::endl;

	int n = 0;
	std::cout << "Enter the fibonacci number: ";
	std::cin >> n;
	std::cin.ignore();

	std::thread thread(fibonacci, n);
	thread.join();

	std::cout << "Main Thread: " << std::this_thread::get_id() << std::endl;

	for (int item : fib_sequence)
	{
		std::cout << item << std::endl;
	}

	std::cin.get();
}