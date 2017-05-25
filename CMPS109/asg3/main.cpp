// Seongwoo Choi
// scho29
// 1368039
// asg3 - listmap-templates

//Imported Libraries here:
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

// I was not so sure, but I decided to add this line
// because otherwise I would get an error message. 
// The terminal says that comparing a string 
// literal with argv[i]
const string CIN = "-";

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}


void print_pair(const string& key, const string& value) {
   cout << key << " = " << value << endl;
}

// Here is keyvalue. Needs to be modified. 
// Try to finish this part by Wednesday.
void keyvalue(str_str_map& map, const string& filename = CIN, 
   istream& file = cin) {
   for(int line_num = 1;; ++line_num) {
      string line;
      getline(file, line);
      if(file.eof())
         break;
      cout << filename << ": " << line_num << ": " << line << endl;
      line = trim(line);
      
      // Empty 
      if(line.empty())
         continue;
      if(line[0] == '#')
         continue;
      
      // why is this part not working?
      auto pos = line.find_first_of("=");
      if(pos == string::npos) {
         // Key:
         auto itor = map.find(line);
         if(itor != map.end())
            print_pair(itor->first, itor->second);
         else
            cout << line << ": key not found" << endl;
      } else {
         string key = trim(line.substr(0, pos));
         string value = trim(line.substr(pos+1));
         str_str_pair pair(key, value);
         if(!key.empty()) {
            if(value.empty()) {
               // key =
               auto itor = map.find(key);
               if(itor != map.end())
                  map.erase(itor);
            } else {
               // key = value
               map.insert(pair);
               print_pair(key, value);
            }
         } else {
            if(value.empty()) {
               // =
               for(auto itor = map.begin(); itor != map.end(); ++itor)
                  print_pair(itor->first, itor->second);
            } else {
               // = value
               for(auto itor = map.begin(); itor != map.end(); ++itor)
                  if(itor->second == value)
                     print_pair(itor->first, itor->second);
            }
         }
      }
   }
}

// Modified main. It is different from the original source given.
int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);
   str_str_map listmap;
   
   if(argc == 1)
      keyvalue(listmap);
   for(int i = 1; i < argc; ++i) {
      if(argv[i] == CIN) {
         keyvalue(listmap);
      } else {
         ifstream file(argv[i]);
         // This area checks to see if file exists.
         if(file.fail()) {
            complain() << argv[i] << ": No such file or directory" 
                       << endl;
            continue;
         }
         keyvalue(listmap, argv[i], file);
         file.close();
      }
   }
   
   return sys_info::get_exit_status();
}

