#ifndef __WindowsErrorException_h__
#define __WindowsErrorException_h__

#include <exception>

namespace teragon {
  namespace plugincore {
    class WindowsErrorException : public std::exception {
    public:
      WindowsErrorException(DWORD errorCode);
      ~WindowsErrorException();

      const char* what() const throw() { return this->message.c_str(); }

    private:
      std::string getFormattedErrorMessage(DWORD errorCode);

      std::string message;
    };
  }
}

#endif