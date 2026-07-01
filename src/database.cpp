#include "database.h"
#include <iostream>
#include <fstream>
#include <thread>

Database::Database(std::filesystem::path storage_path)
	: storage_path_(storage_path) {
	if (!std::filesystem::exists(storage_path_)) {
		std::filesystem::create_directories(storage_path_);
	}
	std::cout << "[DB] Initialized. Storage: " << storage_path_ << "\n";
}

void Database::writeString(const std::string& key, const std::string& value) {
	std::lock_guard<std::mutex> lock(db_mutex_);
	std::filesystem::path full_path = storage_path_ / (key + ".txt");
	std::ofstream file(full_path);
	if (file.is_open()) {
		file << value << "\n";
		std::cout << "[Thread " << std::this_thread::get_id() << "] Writing: "
			<< key << " = \"" << value << "\"\n";
	}
}

std::optional<std::string> Database::readString(const std::string& key) const {
	std::lock_guard<std::mutex> lock(db_mutex_);
	std::filesystem::path full_path = storage_path_ / (key + ".txt");
	if (std::filesystem::exists(full_path)) {
		std::ifstream fin(full_path);
		if (fin.is_open()) {
			std::string text;
			if (std::getline(fin, text))
				return text;
		}
	}
	return std::nullopt;
}