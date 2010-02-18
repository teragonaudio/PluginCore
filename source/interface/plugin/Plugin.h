/*
 *  Plugin.h
 *  plugincore
 *
 *  Created by Nik Reiman on 2010-01-14.
 *  Copyright 2010 Singbox AB. All rights reserved.
 *
 */

#include "AudioBufferSet.h"

namespace teragon {
  namespace plugincore {
	class Plugin {
		Plugin();
		virtual ~Plugin();
		
		virtual void initialize() = 0;
		virtual void process(const AudioBufferSet& inputs, AudioBufferSet& outputs, const BufferIndex frames) = 0;
		
	};
}
}