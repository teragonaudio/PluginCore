#!/usr/bin/python
import distutils.dir_util
import distutils.file_util
import os.path
import subprocess
import sys

wrapperPath = os.path.abspath(sys.argv[1])
dylibPath = os.path.abspath(sys.argv[2])
pluginIdent = sys.argv[3]
pluginName = os.path.basename(dylibPath).split('.')[0]
pluginPath = os.path.join(os.path.dirname(dylibPath), pluginName + ".vst")

print "Creating", pluginPath
distutils.dir_util.copy_tree(wrapperPath, pluginPath, verbose = 1)

pluginContentsPath = os.path.join(pluginPath, 'Contents')
distutils.file_util.copy_file(dylibPath, os.path.join(pluginContentsPath, 'Resources'), verbose = 1)

infoPlistPath = os.path.join(pluginContentsPath, 'Info')
subprocess.call(["defaults", "write", infoPlistPath, 'CFBundleIdentifier', pluginIdent ])
