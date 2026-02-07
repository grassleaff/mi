#include "include/flm.hpp"
#include <filesystem>

namespace fs = std::filesystem;

FLM::FLM() : opened(false), selected(0) {}

void FLM::toggle() {
    opened = !opened;
    if (opened)
        load_directory();
}

bool FLM::is_open() const {
    return opened;
}

int FLM::width() const {
    return opened ? 30 : 0;
}

void FLM::load_directory() {
    entries.clear();
    for (auto& p : fs::directory_iterator(fs::current_path())) {
        entries.push_back(p.path().filename().string());
    }
    selected = 0;
}

void FLM::render(int rows) {

    if (!opened) return;

    attron(A_REVERSE);
    mvhline(0, 0, ' ', 30);
    mvprintw(0, 1, " FLM ");
    attroff(A_REVERSE);

    for (int i = 0; i < rows - 2 && i < (int)entries.size(); i++) {
        if (i == selected)
            attron(A_REVERSE);

        mvprintw(i + 1, 1, "%-28s", entries[i].c_str());

        if (i == selected)
            attroff(A_REVERSE);
    }

    for (int i = 0; i < rows; i++)
        mvaddch(i, 29, ACS_VLINE);
}

bool FLM::handle_input(int ch, std::string& selected_file) {

    if (!opened) return false;

    switch (ch) {
        case KEY_UP:
            if (selected > 0) selected--;
            break;

        case KEY_DOWN:
            if (selected < (int)entries.size() - 1)
                selected++;
            break;

        case '\n':
            selected_file = entries[selected];
            return true;
    }

    return false;
}

