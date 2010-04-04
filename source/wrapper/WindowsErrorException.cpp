#if WINDOWS

#ifndef __WindowsErrorException_h__
#include "WindowsErrorException.h"
#endif

#include <sstream>

namespace teragon {
  namespace plugincore {
    WindowsErrorException::WindowsErrorException(DWORD errorCode) : std::exception() {
      this->message = getFormattedErrorMessage(errorCode);
    }

    WindowsErrorException::~WindowsErrorException() {
    }

    std::string WindowsErrorException::getFormattedErrorMessage(DWORD errorCode) {
      std::string result;

      LPTSTR errorMessage = NULL;
      DWORD status = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        NULL,
        errorMessage,
        0,
        NULL);
      if(status == 0 || errorMessage == NULL) {
        std::stringstream numberFormatter;
        numberFormatter << errorCode;
        result = numberFormatter.str();
      }
      else {
        result.assign(errorMessage);
        LocalFree(errorMessage);
      }

      return result;
    }
  }
}

#endif
