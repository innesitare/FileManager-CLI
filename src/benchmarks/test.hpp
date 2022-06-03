#include "libs/UI/FileSystemUI.h"
#include <cxxopts.hpp>
#include <filesystem>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>
#include <string>

cxxopts::ParseResult parseArgs(cxxopts::Options opts, const int* argc, char*** argv)
{
    try {
        cxxopts::ParseResult res = opts.parse(*argc, *argv);
        return res;
    }
    catch (const cxxopts::OptionParseException& e) {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

void Start(const FileSystemOptions& options)
{
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    std::shared_ptr<FileSystemUI> ui = ftxui::Make<FileSystemUI>(options);

    ui->setQuitFunction(screen.ExitLoopClosure());
    screen.Loop(ui);
}

std::filesystem::path normalizePath(std::filesystem::path p)
{
    p = p.lexically_normal();
    return p.is_absolute() ? p : std::filesystem::current_path() / p;
}

int Benchmark(int argc, char* argv[]) {
    cxxopts::Options cliOptions(PROJECT_NAME, PROJECT_DESCRIPTION);

    cliOptions.add_options()
        ("h,help", "Prints this help messange")
        ("v,version", "Prints version")
        ("a,all", "List entries starting with .", cxxopts::value<bool>()->default_value("false"))
        ("p,path", "Change starting path", cxxopts::value<std::string>()->default_value({}));

    auto cliResult = parseArgs(cliOptions, &argc, &argv);

    if (cliResult.count("help") != 0U) {
        std::cout << cliOptions.help() << std::endl;
        return 0;
    }

    if (cliResult.count("version") != 0U) {
        std::cout << PROJECT_NAME << "'s version: " << PROJECT_VERSION << std::endl;
        return 0;
    }

    FileSystemOptions options;
    if (cliResult["path"].as<std::string>().empty()) {
        options.path = std::filesystem::current_path();
    }
    else {
        try {
            options.path = normalizePath(cliResult["path"].as<std::string>());
        }
        catch (std::filesystem::filesystem_error& error) {
            std::cerr << "Can't open parsed path" << std::endl;
            return 1;
        }
    }
    options.showHiddenFiles = cliResult["all"].as<bool>();

    Start(options);
    return 0;
}