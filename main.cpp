#include <sstream>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>

#include "tree.h"

#define NAME "TTY"

using namespace std;

vector<string> split(string &s) {
    vector<string> e;
    stringstream ss(s);
    string item;
    while (ss >> item) { // ambil satu kata
        e.push_back(item);
    }
    return e;
}

int main()
{
    adrNode root;
    createNode(root, "/", DATA_DIR);

    vector<adrNode> dir;
    dir.push_back(root);

    cout << "Welcome to " << NAME << endl;
    while (true) {

        adrNode cwd = dir.back();

        string input;

        cout << "[ user@tty ";
        printPath(dir);
        cout << "] $ ";

        getline(cin, input);
        vector<string> args = split(input);
        string cmd = args[0];

        if (cmd == "exit") return 0;
        else if (cmd == "clear") cout << "\033[2J\033[H"; // clear screen

        else if (cmd == "ls") { // List directory
            adrNode target = cwd;

            if (args.size() == 2) { // argument size 2: berarti ls ke directory lain
                string name = args[1];

                bool found = false;
                for (adrNode child : cwd->child) {
                    if (child->name == name) {
                        target = child;
                        found = true;
                        break;
                    } // kalo ketemu, ganti target dengan child
                }

                if (!found) {
                    cout << "Folder tidak ditemukan!" << endl;
                    continue;
                }
            }

            if (target->child.empty()) {
                cout << "[Kosong]" << endl;
            }
            else {
                for (adrNode child : target->child) {
                    if (child->type == DATA_DIR) cout << "[DIR]  ";
                    else if (child->type == DATA_FILE) cout << "[FILE] ";
                    else cout << "[UNKWN] ";

                    cout << right << setw(6) << child->content.length();
                    cout << " " << child->name << endl;
                }
            }
        }

        else if (cmd == "mv") {
            if (args.size() < 3) cout << "Penggunaan: mv <old_name> <new_name>" << endl;
            else {
                string oldname = args[1];
                string newname = args[2];

                if (findChild(cwd->child, oldname) == nullptr) {
                    cout << "File tidak ditemukan" << endl;
                    continue;
                }

                for (adrNode child : cwd->child) {
                    if (child->name == oldname) {
                        child->name = newname;
                        continue;
                    }
                }
            }
        }

        else if (cmd == "touch") {
            if(args.size() < 2) cout << "Penggunaan: touch <file_name>"; // argument kurang dari 2 "nama file tidak ada"
            else {
                if (!addChild(cwd, args[1], DATA_FILE)) cout << "File/folder sudah ada!" << endl;
            }
        }

        else if (cmd == "mkdir") {
            if(args.size() < 2) cout << "Penggunaan: mkdir <dir>"; // argument kurang dari 2 "nama file tidak ada"
            else {
                if (!addChild(cwd, args[1], DATA_DIR)) cout << "File/folder sudah ada!" << endl;
            }
        }

        else if (cmd == "cd") {
            if(args.size() < 2) cout << "Penggunaan: cd <dir> / cd .."; // argument kurang dari 2 "nama file tidak ada"
            else {
                string dirname = args[1];

                if (dirname == "..") dir.pop_back();
                else {
                    adrNode child = findChild(cwd->child, dirname);
                    if (child == nullptr) cout << "Tidak ditemukan" << endl;
                    else if (child->type != DATA_DIR) cout << "Bukan directory" << endl;
                    else dir.push_back(child);
                }
            }
        }

        else if (cmd == "rm") {
            if(args.size() < 2) cout << "Penggunaan: cd <dir> / cd .."; // argument kurang dari 2 "nama file tidak ada"
            else {
                string target = args[1];

                adrNode child = findChild(cwd->child, target);
                if (child == nullptr) cout << "Tidak ada file/folder dengan nama \"" << target << "\" Ditemukan!" << endl;
                else {
                    deleteChild(cwd, target);
                    deleteTree(child);
                }
            }
        }

        else if (cmd == "write") {
            if (args.size() < 3) {
                cout << "Penggunaan: write <file> <data>" << endl;
                continue;
            }

            adrNode file = findChild(cwd->child, args[1]);

            if (file == nullptr) cout << "File tidak ditemukan!" << endl;
            else if (file->type != DATA_FILE) cout << "Bukan File!";
            else {
                string content = "";
                for (int i = 2; i < args.size(); i++) { // i mulai dari 2 karena mengabaikan cmd dan file name
                    content += args[i] + " ";
                }

                file->content = content;
            }
        }

        else if (cmd == "cat") {
            if (args.size() < 2) {
                cout << "Penggunaan: cat <file>" << endl;
                continue;
            }

            adrNode file = findChild(cwd->child, args[1]);

            if (file == nullptr) cout << "File tidak ditemukan!" << endl;
            else if (file->type != DATA_FILE) cout << "Bukan File!";
            else {
                cout << file->content << endl;
            }
        }

        else if (cmd == "treepre") {
            preorder(cwd);
        }

        else if (cmd == "treepost") {
            postorder(cwd);
        }

        else cout << "Perintah tidak valid!" << endl;
    }

    return 0;
}
