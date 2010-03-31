#ifndef __PluginLoaderException_h__
#define __PluginLoaderException_h__

#include <exception>
#include <string>

namespace teragon {
  namespace plugincore {
    class PluginLoaderException : public std::exception {
    public:
      PluginLoaderException(std::string message) : exception() { this->message = message; }
      ~PluginLoaderException() {}

      const char* what() const throw() { return this->message.c_str(); }

    private:
      std::string message;
    };
  }
}

#endif