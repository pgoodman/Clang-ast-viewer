#ifdef _WIN32
#include <windows.h>
#else
#include <wordexp.h>
#endif

#include <vector>
#include <string>
#include <cassert>

std::vector<std::string> splitCommandLine(std::string const &command)
{
  size_t data_size = (command.size() * 2) + 1;

  std::unique_ptr<char[]> data(new char[data_size]);

  std::vector<std::string> argv;

  auto arg_data_ptr = &(data[0]);
  memset(arg_data_ptr, 0, data_size);

  auto last_token = arg_data_ptr;

  bool prev_is_escaped = false;
  bool in_container = false;
  char container_ch = '\0';

  for (size_t i = 0; i < command.size(); ) {
    const auto ch = command[i++];
    if ('\\' == ch) {
      if (prev_is_escaped) {
        *arg_data_ptr++ = ch;
        prev_is_escaped = false;
        continue;

      } else if (in_container) {
        *arg_data_ptr++ = ch;
        continue;

      } else {
        prev_is_escaped = true;
      }

    } else if (' ' == ch || '\t' == ch || '\r' == ch || '\n' == ch) {
      if (prev_is_escaped) {
        prev_is_escaped = false;

      } else if (in_container) {
        *arg_data_ptr++ = ch;

      } else if (last_token[0]) {
        *arg_data_ptr++ = '\0';
        argv.push_back(last_token);
        last_token = arg_data_ptr;
      }

    } else if ('"' == ch || '\'' == ch) {
      if (prev_is_escaped) {
        *arg_data_ptr++ = '\\';
        *arg_data_ptr++ = ch;
        prev_is_escaped = false;

      } else if (in_container) {
        *arg_data_ptr++ = ch;
        if (ch == container_ch) {
          in_container = false;
          container_ch = '\0';
        }

      } else {
        *arg_data_ptr++ = ch;
        in_container = true;
        container_ch = ch;
      }
    } else {
      *arg_data_ptr++ = ch;
    }
  }

  if (last_token[0]) {
    *arg_data_ptr++ = '\0';
    argv.push_back(last_token);
  }

  return argv;
}