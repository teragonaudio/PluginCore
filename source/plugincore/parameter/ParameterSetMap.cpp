#ifndef __ParameterSetMap_h__
#include "ParameterSetMap.h"
#endif

namespace teragon {
  namespace plugincore {
    ParameterSetMap::ParameterSetMap() : PluginParameterSet() {
    }

    ParameterSetMap::~ParameterSetMap() {
    }

    PluginParameter* ParameterSetMap::getParameter(const ParameterName name) const {
      ParameterSetMapStorage::const_iterator iterator = parameterStorage.find(name);
      return (iterator != NULL) ? iterator->second : NULL;
    }
    
    const int ParameterSetMap::size() const {
      return parameterStorage.size();
    }
  }
}
