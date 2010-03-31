#ifndef __ParameterSetMap_h__
#include "ParameterSetMap.h"
#endif

namespace teragon {
  namespace plugincore {
    ParameterSetMap::ParameterSetMap() : PluginParameterSet() {
    }

    ParameterSetMap::~ParameterSetMap() {
    }

    void ParameterSetMap::addParameter(PluginParameter* parameter) {
      parameterStorage.insert(make_pair(parameter->getName(), parameter));
    }

    PluginParameter* ParameterSetMap::getParameter(const ParameterIndex index) const {
      ParameterSetMapStorage::const_iterator iterator = parameterStorage.begin();
      if(iterator != parameterStorage.end()) {
        // TODO: This is very inefficient...
        for(int i = 0; i < index; ++i) {
          iterator++;
        }
        return iterator->second;
      }
      else {
        return NULL;
      }
    }

    PluginParameter* ParameterSetMap::getParameter(const ParameterString name) const {
      ParameterSetMapStorage::const_iterator iterator = parameterStorage.find(name);
      return (iterator != parameterStorage.end()) ? iterator->second : NULL;
    }
    
    const int ParameterSetMap::size() const {
      return parameterStorage.size();
    }
  }
}
