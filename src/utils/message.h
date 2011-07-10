#ifndef DVG_SRC_UTILS_MESSAGE_H_
#define DVG_SRC_UTILS_MESSAGE_H_

#include <stdint.h>

#include <sstream>
#include <string>

namespace dvg {
namespace utils {

class Message {
 //FUNCTIONS
 public:
  explicit Message(uint32_t header)
  : buffer_(std::ios_base::in | std::ios_base::out | std::ios_base::binary),
    header_(header) {}
  virtual ~Message() {}

  uint32_t GetHeader() {
    buffer_.seekg(0);
    return header_;
  }

  template<typename T>
  T Read();

  template<typename T>
  void Write(const T &val);

 //VARIABLES
 private:
  uint32_t header_;
  std::stringstream buffer_;
};

template<class T>
T Message::Read() {
  T val;
  buffer_.read((char*)(&val), sizeof(val));
  return val;
}

template<>
std::string Message::Read <std::string> () {
  uint16_t size = this->Read<uint16_t>();
  char* buf = new char[size+1];
  buffer_.read(buf, size+1);
  std::string val(buf, size);
  delete [] buf;
  return val;
}

template<class T>
void Message::Write(const T &val) {
  buffer_.write((char*)(&val), sizeof(val));
}

template<>
void Message::Write <std::string> (const std::string& val) {
  uint16_t size = (uint16_t)val.size();
  this->Write<uint16_t>(size);
  buffer_.write(val.c_str(), size+1);
}

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_MESSAGE_H_
