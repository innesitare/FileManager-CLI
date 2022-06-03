#pragma once
#include <iostream>
#include <filesystem>
#include <future>
#include <vector>
#include <algorithm>

class FileSystemOperations {
public:
    enum Operation {
        NOT_SELECTED,
        COPY,
        DELETE,
        MOVE,
    };

    std::vector<std::filesystem::path> getSelectedFiles();
    void setSelectedFiles(const std::vector<std::filesystem::path>&);
    void appendSelectedFiles(const std::filesystem::path&);
    void clearSelectedFiles();
    size_t countSelectedFiles();

    void setOperation(Operation);
    Operation getOperation();
    void clearOperation();

    void performOperation(const std::filesystem::path&);

    void clearLastOperationStatus();
    bool lastOperationIsCompleated();

private:
    std::vector<std::filesystem::path> selectedFiles;
    Operation selectedOperation = NOT_SELECTED;
    std::future<bool> lastOperationCompleated;
};
