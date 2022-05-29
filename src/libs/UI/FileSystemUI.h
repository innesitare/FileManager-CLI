#pragma once
#include "..\operations\FileSystemOperations.h"
#include <filesystem>
#include <ftxui/component/component.hpp>
#include <ftxui/component/menu.hpp>

struct FileSystemOptions {
    bool showHiddenFiles;
    std::filesystem::path path;
};

class FileSystemUI : public ftxui::ComponentBase {
private:
    std::function<void()> quit;
    std::wstring spaceInfo, statusMessage, statusSelected, operationView, currentPathCached;
    std::filesystem::path currentPath;
    std::vector<std::wstring> parentFolderEntries;
    std::vector<std::wstring> currentFolderEntries;
    int parentFolderSelected = 0;
    int currentFolderSelected = 0;
    ftxui::Component parentFolder = ftxui::Menu(&parentFolderEntries, &parentFolderSelected);
    ftxui::Component currentFolder = ftxui::Menu(&currentFolderEntries, &currentFolderSelected);
    float diskSpaceAvailable;
    bool isShowingHiddenFile;

    void updateParentView();
    void updateMainView(size_t = 0);
    void updateOperationView();
    void updateSelectedCounter();
    void updateAllUi(size_t = 0);

    void changePathAndUpdateViews(const std::filesystem::path&);
    void selectFile(const std::filesystem::path&);
    void toggleHiddenFiles();
    void selectOperation(FileSystemOperations::Operation);
    void performOperation(const std::filesystem::path&);

    FileSystemOperations filesystemOperations;

public:
    FileSystemUI(const FileSystemOptions&);

    void setQuitFunction(std::function<void()>);

    ftxui::Element Render() override;
    bool OnEvent(ftxui::Event) override;
};
