#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Task {
    std::string title;
    bool done = false;
};

const std::string FILE_NAME = "tasks.txt";

// File format: one task per line -> "0|title" (not done) or "1|title" (done)
std::vector<Task> loadTasks() {
    std::vector<Task> tasks;
    std::ifstream in(FILE_NAME);
    std::string line;
    while (std::getline(in, line)) {
        if (line.size() < 3 || line[1] != '|') continue;  // skip bad lines
        tasks.push_back({line.substr(2), line[0] == '1'});
    }
    return tasks;
}

void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream out(FILE_NAME);
    for (const Task& t : tasks) out << (t.done ? '1' : '0') << '|' << t.title << '\n';
}

// Converts "3" to index 2. Returns -1 if the text is not a valid task number.
int parseIndex(const std::string& text, size_t count) {
    try {
        size_t pos = 0;
        int n = std::stoi(text, &pos);
        if (pos != text.size() || n < 1 || n > static_cast<int>(count)) return -1;
        return n - 1;
    } catch (const std::exception&) {
        return -1;
    }
}

void printUsage() {
    std::cout << "Usage:\n"
                 "  ./todo add <title>\n"
                 "  ./todo list\n"
                 "  ./todo done <number>\n"
                 "  ./todo delete <number>\n";
}

int main(int argc, char** argv) {
    if (argc < 2) { printUsage(); return 1; }

    std::string cmd = argv[1];
    std::vector<Task> tasks = loadTasks();

    if (cmd == "add") {
        std::string title;
        for (int i = 2; i < argc; i++) title += (i > 2 ? " " : "") + std::string(argv[i]);
        if (title.empty()) { std::cout << "Error: title cannot be empty\n"; return 1; }
        tasks.push_back({title, false});
        saveTasks(tasks);
        std::cout << "Added task " << tasks.size() << "\n";
    } else if (cmd == "list") {
        if (tasks.empty()) std::cout << "No tasks\n";
        for (size_t i = 0; i < tasks.size(); i++)
            std::cout << i + 1 << ". [" << (tasks[i].done ? 'x' : ' ') << "] " << tasks[i].title << "\n";
    } else if ((cmd == "done" || cmd == "delete") && argc >= 3) {
        int i = parseIndex(argv[2], tasks.size());
        if (i < 0) { std::cout << "Error: invalid task number\n"; return 1; }
        if (cmd == "done") tasks[i].done = true;
        else tasks.erase(tasks.begin() + i);
        saveTasks(tasks);
        std::cout << "OK\n";
    } else {
        printUsage();
        return 1;
    }
    return 0;
}
