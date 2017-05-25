// $Id: cix.cpp,v 1.4 2016-05-09 16:01:56-07 - - $
// Seongwoo Choi
// scho29
// 1368039

#include <iostream>
#include <cerrno>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "protocol.h"
#include "logstream.h"
#include "sockets.h"

logstream log (cout);
struct cix_exit: public exception {};

string trim (const string &str) {
   size_t first = str.find_first_not_of(" \t");
   if (first == string::npos) return "";
   size_t last = str.find_last_not_of(" \t");
   return str.substr(first, last - first + 1);
}

unordered_map<string,cix_command> command_map {
   {"exit", cix_command::EXIT},
   {"help", cix_command::HELP},
   {"ls"  , cix_command::LS  },
   {"get" , cix_command::GET },
   {"put" , cix_command::PUT },
   {"rm"  , cix_command::RM  },
};

void cix_help() {
   static const vector<string> help = {
      "exit         - Exit the program.  Equivalent to EOF.",
      "get filename - Copy remote file to local host.",
      "help         - Print help summary.",
      "ls           - List names of files on remote server.",
      "put filename - Copy local file to remote host.",
      "rm filename  - Remove file from remote server.",
   };
   for (const auto& line: help) cout << line << endl;
}

void cix_rm(client_socket &server, string filename) {
   cix_header header;
   header.command = cix_command::RM;
   if(filename.size() >= FILENAME_SIZE) {
      log << "rm: " << filename << ": filename too long" << endl;
      return;
   }
   strcpy(header.filename, filename.c_str());
   header.nbytes = 0;
   log << "sending header " << header << endl;
   send_packet(server, &header, sizeof header);
   recv_packet(server, &header, sizeof header);
   log << "received header " << header << endl;
   if(header.command != cix_command::ACK) {
      log << "sent RM, server did not return ACK" << endl;
      log << "server returned " << header << endl;
      log << "rm: " << strerror(header.nbytes) << endl;
      return;
   }
   log << "successful rm" << endl;
}

void cix_put (client_socket& server, string filename) {
   cix_header header;
   header.command = cix_command::PUT;
   if(filename.size() >= FILENAME_SIZE) {
      log << "put: " << filename << ": filename too long" << endl;
      return;
   }
   ifstream ifs(filename);
   if(!ifs.good()) {
      log << "put: " << strerror(errno) << endl;
      return;
   }
   stringstream stream;
   stream << ifs.rdbuf();
   string bytes = stream.str();
   strcpy(header.filename, filename.c_str());
   header.nbytes = bytes.size();
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   send_packet (server, bytes.c_str(), bytes.size());
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if(header.command != cix_command::ACK) {
      log << "sent PUT, server did not return ACK" << endl;
      log << "server returned " << header << endl;
      log << "put: " << strerror(header.nbytes) << endl;
      return;
   }
   log << "put successful" << endl;
}

void cix_get (client_socket& server, string& filename) {
   cix_header header;
   header.command = cix_command::GET;
   if(filename.size() >= FILENAME_SIZE) {
      log << "get: " << filename << ": filename too long" << endl;
      return;
   }
   strcpy(header.filename, filename.c_str());
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if(header.command != cix_command::FILE) {
      log << "sent GET, server did not return FILE" << endl;
      log << "server returned " << header << endl;
      log << "get: " << strerror(header.nbytes) << endl;
   } else {
      ofstream ofs{filename};
      char buffer[header.nbytes + 1];
      recv_packet (server, buffer, header.nbytes);
      log << "received " << header.nbytes << " bytes" << endl;
      buffer[header.nbytes] = '\0';
      ofs.write(buffer, header.nbytes);
      ofs.close();
      log << "get successful" << endl;
   }
}

void cix_ls (client_socket& server) {
   cix_header header;
   header.command = cix_command::LS;
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.command != cix_command::LSOUT) {
      log << "sent LS, server did not return LSOUT" << endl;
      log << "server returned " << header << endl;
      log << "ls: " << strerror(header.nbytes) << endl;
   }else {
      char buffer[header.nbytes + 1];
      recv_packet (server, buffer, header.nbytes);
      log << "received " << header.nbytes << " bytes" << endl;
      log << "ls successful" << endl;
      buffer[header.nbytes] = '\0';
      cout << buffer;
   }
}


void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   if (args.size() > 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   if(args.size() == 1) {
      size_t pos = args[0].find(".");
      int hostn = 0, portn = 0;
      if(pos == string::npos)
         hostn = 1;
      else
         portn = 1;
      host = get_cix_server_host (args, hostn);
      port = get_cix_server_port (args, portn);
   }
   log << to_string (hostinfo()) << endl;
   try {
      log << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      log << "connected to " << to_string (server) << endl;
      for (;;) {
         string line;
         getline (cin, line);
         if (cin.eof()) throw cix_exit();
         log << "command " << line << endl;
         string input{}, command{}, filename{};
         bool over_two = false;
         input = trim(line);
         if(input.size() == 0) continue;
         size_t pos = input.find(" ");
         if(pos == string::npos) {
            command = input;
         } else {
            command = input.substr(0, pos);
            if(input.find(" ", pos + 1) == string::npos) {
               filename = input.substr(pos + 1);
               if(filename.find("/") != string::npos) {
                  log << "filename cannot have a slash" << endl;
                  continue;
               }
            } else {
               over_two = true;
            }
         }
         const auto& itor = command_map.find (command);
         cix_command cmd = itor == command_map.end()
                         ? cix_command::ERROR : itor->second;
         switch (cmd) {
            case cix_command::EXIT:
               if(filename.size() > 0 or over_two) {
                  log << "exit: usage: exit" << endl;
                  continue;
               }
               throw cix_exit();
               break;
            case cix_command::HELP:
               if(filename.size() > 0 or over_two) {
                  log << "help: usage: help" << endl;
                  continue;
               }
               cix_help();
               break;
            case cix_command::LS:
               if(filename.size() > 0 or over_two) {
                  log << "ls: usage: ls" << endl;
                  continue;
               }
               cix_ls (server);
               break;
            case cix_command::GET:
               if(filename.size() == 0 or over_two) {
                  log << "get: usage: get filename" << endl;
                  continue;
               }
               cix_get(server, filename);
               break;
            case cix_command::PUT:
               if(filename.size() == 0 or over_two) {
                  log << "put: usage: put filename" << endl;
                  continue;
               }
               cix_put(server, filename);
               break;
            case cix_command::RM:
               if(filename.size() == 0 or over_two) {
                  log << "rm: usage: rm filename" << endl;
                  continue;
               }
               cix_rm(server, filename);
               break;
            default:
               log << input << ": invalid command" << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   return 0;
}



