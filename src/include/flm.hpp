#pragma once
#include <vector>
#include <string>
#include <ncurses.h>

class FLM {
public:
    FLM();

    void toggle();
    void render(int rows);
    bool handle_input(int ch, std::string& selected_file);

    bool is_open() const;
    int  width() const;

private:
    bool opened;
    int selected;
    std::vector<std::string> entries;

    void load_directory();
};

