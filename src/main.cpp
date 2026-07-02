#include "database.h"
#include <iostream>
#include <thread>

void workerThread(Database& db, int thread_num) {
	for (int i = 0; i < 10; i++) {
		std::string key = "thread" + std::to_string(thread_num) + "_log" + std::to_string(i);
		std::string value = "Log entry " + std::to_string(i) + " from thread " + std::to_string(thread_num);
		db.writeString(key, value);
	}
}

int main() {
	Database db("db_storage");

	std::thread t1(workerThread, std::ref(db), 1);
	std::thread t2(workerThread, std::ref(db), 2);
	std::thread t3(workerThread, std::ref(db), 3);

	t1.join();
	t2.join();
	t3.join();

	std::cout << "All threads finished working" << "\n";


	std::string existing_key = "thread1_log0";
	auto res1 = db.readString(existing_key);

	if (res1)
		std::cout << "Key '" << existing_key << "' found" << "\n";
	else
		std::cout << "Key '" << existing_key << "' not found\n";
	

	std::string fake_key = "non_existent_key";
	auto result2 = db.readString(fake_key);

	if (result2)
		std::cout << "Key '" << fake_key << "' found" << "\n";
	else
		std::cout << "Key '" << fake_key << "' not found" << "\n"; 

	return 0;
}