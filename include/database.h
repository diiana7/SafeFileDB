#pragma once
#include <filesystem>
#include <mutex>
#include <optional>
#include <string>
#include <type_traits>

class Database {
private:
	std::filesystem::path storage_path_;
	mutable std::mutex db_mutex_;
public:
	Database(std::filesystem::path storage_path);

	void writeString(const std::string& key, const std::string& value);

	template<typename T>
	requires std::is_arithmetic_v<T>
	void writeNumber(const std::string& key, T value) {
		writeString(key, std::to_string(value));
	}

	std::optional<std::string> readString(const std::string& key) const;
};

