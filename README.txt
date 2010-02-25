PluginCore is a framework for creating audio processing plugins for sequencers or trackers.  It aims to abstract away as much of the underlying plugin and platform API as possible, and allow rapid development of audio plugins with a high degree of testability.  Currently, PluginCore supports the VST and AudioUnit protocols for both effect and instrument plugins.

PluginCore contains two components: the actual plugin interface, and wrapper plugins for each supported platform.  To create a new plugin, one must create a new dynamic library which implements the a single plugin interface, and copy and rename the wrapper plugins which will the end user will copy into their plugin folder.  Further instructions on development and redistribution can be found in the official project documentation.

This project is hosted at the following addresses:

Project Page: http://www.teragon.org/p/PluginCore.html
Source Code: http://www.github.com/teragonaudio/plugincore
Issue Tracker: http://teragonaudio.lighthouseapp.com/projects/47371-plugincore
