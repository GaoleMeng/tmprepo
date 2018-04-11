// compiler with 
// g++ -std=c++17  generate_first.cpp -o generate_first -lstdc++fs -pthread
// the first round of the multithread version of the processing file

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <regex>
#include <experimental/filesystem>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
// #include <boost/range/iterator_range.hpp>
namespace fs = std::experimental::filesystem;
using namespace std;
using namespace rapidjson;

string input_dir_1 = "/scratch/si699w18_fluxm/gaole/aminer_papers_0";
string input_dir_2 = "/scratch/si699w18_fluxm/gaole/aminer_papers_1";
string input_dir_3 = "/scratch/si699w18_fluxm/gaole/aminer_papers_2";
string output_file = "/scratch/si699w18_fluxm/gaole/cpp_largevis_first.txt";
vector<string> dir_list = {input_dir_1, input_dir_2, input_dir_3};
string lastfix = ".txt";

static mutex output_lock;
mutex parselock;
ofstream output;
string tmp = "";
vector<string> filedir_list;
regex id("\"id\": \".*?\"");
regex venue("\"venue\": \".*?\"");
regex references("\"references\": \\[.*?\\]");
regex single_id("\".{24}\"");

void read_and_parse(int indices) {
    // cout << filename << "\n";
    
    string filename = filedir_list[indices];
    
    ifstream input(filename.c_str());
    string line = "";
    
    while(getline(input, line)) {
        // Document d;
        // parselock.lock();
        // if (!d.HasMember("id")) {
        //     // parselock.unlock();
        //     parselock.unlock();
        //     continue;
        // }
        // if (!d.HasMember("venue")) {
        //     parselock.unlock();
        //     continue;
        // }
        // if (d["venue"].GetString() != "SIGIR") {
        //     parselock.unlock();
        //     continue;
        // }
        smatch id_extract;
        if (regex_search(line, id_extract, id)){
            smatch venue_extract; 
            if (regex_search(line, venue_extract, venue)) {
                string reference_string = "";
                if (venue_extract[0] != "\"venue\": \"SIGIR\"") continue


                string id_string = id_extract[0].substr(7, 24);
                string refer_string = "";
                smatch references_extract;
                if (regex_search(line, references_extract, references)) {
                    string whole_string = references_extract[0];
                    int start = 16;
                    while (start < whole_string.length()) {
                        refer_string.append(whole_string.substr(start, 24) + " ");
                        start += 28;
                    }
                }
                output_lock.lock();
                cout << id_string + " SIGIR " + refer_string << "\n";
                output_lock.unlock();
            }
        }
        break;
    }
}


int main() {
    vector<thread> thread_list;
    output.open(output_file);

    for (string dir: dir_list) {
        for (auto & p : fs::directory_iterator(dir)) {
            if (strstr(p.path().filename().c_str(), lastfix.c_str())) {
                filedir_list.push_back(p.path());                
            }
        }
    }

    for (int i = 0; i < filedir_list.size(); i++) {
        thread_list.push_back(thread(read_and_parse, i));
        // read_and_parse(i);
    }

    for (auto& th: thread_list) th.join();
    cout << tmp;
    output.close();
}





