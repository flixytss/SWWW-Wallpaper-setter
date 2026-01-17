#include <cstdlib>
#include <fstream>
#include <ncurses.h>
#include <string>
#include <filesystem>

#include <aux.hpp>

void SetWallpaper(const std::filesystem::path path) {
    std::system((std::string){"swww img " + path.string()}.c_str());
    const char* home = std::getenv("HOME");
    if (!home) {
        throw std::runtime_error("HOME not set");
    }
    std::filesystem::path configPath =
        std::filesystem::path(home) / ".local/state/initback.sh";

    std::filesystem::create_directories(configPath.parent_path());

    if (!std::filesystem::exists(configPath)) {
        std::ofstream createFile(configPath);
    }
    std::ofstream createFile(configPath);

    const std::string buffer = "#!/bin/bash\n" + (std::string){"swww img \"" + path.string() + "\""};
    createFile.write(buffer.c_str(), buffer.size());

    createFile.close();
    
}

void PassControl(EntryInfo info) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (!has_colors())
        Finish(1);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    int SelectionIndex = 0;
    int ScrollOffset   = 0;

    bool running = true;

    while (running) {
        clear();

        int height, width;
        getmaxyx(stdscr, height, width);
        

        int headerLines = 2;
        int visibleRows = height - headerLines;
        int fileCount   = info.Files.size();

        if (SelectionIndex < 0)
            SelectionIndex = 0;
        if (SelectionIndex >= fileCount)
            SelectionIndex = fileCount - 1;

        /* Keep selection visible */
        if (SelectionIndex < ScrollOffset)
            ScrollOffset = SelectionIndex;
        else if (SelectionIndex >= ScrollOffset + visibleRows)
            ScrollOffset = SelectionIndex - visibleRows + 1;

        attron(COLOR_PAIR(2));
        printw("WALLPAPERS CLI\n\n");
        attroff(COLOR_PAIR(2));

        for (int i = 0; i < visibleRows; ++i) {
            int fileIndex = ScrollOffset + i;
            if (fileIndex >= fileCount)
                break;

            const std::filesystem::path path(info.Files[fileIndex]);

            if (fileIndex == SelectionIndex)
                attron(COLOR_PAIR(1));

            mvprintw(headerLines + i, 0, "#%d: %s",
                    fileIndex, path.c_str());

            if (fileIndex == SelectionIndex)
                attroff(COLOR_PAIR(1));
        }

        refresh();

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                SelectionIndex--;
                break;
            case KEY_DOWN:
                SelectionIndex++;
                break;
            case KEY_PPAGE: // Page Up
                SelectionIndex -= visibleRows;
                break;
            case KEY_NPAGE: // Page Down
                SelectionIndex += visibleRows;
                break;
            case '\n':
            case KEY_ENTER:
                SetWallpaper(std::filesystem::path(info.Files[SelectionIndex]));
                break;
            case 'q':
                running = false;
                break;
            default:
                break;
        }
    }

    endwin();
}
