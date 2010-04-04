from SCons.Errors import StopError

PluginCoreEnv = Environment()

# Configure preprocessor variables for platform
if PluginCoreEnv['PLATFORM'] == 'darwin':
  PluginCoreEnv.Append(CCFLAGS = ['-DMAC=1'])
elif PluginCoreEnv['PLATFORM'] == 'windows':
  PluginCoreEnv.Append(CCFLAGS = ['-DWINDOWS=1', '-DWIN32=1'])
else:
  raise Error, "Sorry, PluginCore is not supported this platform"

AddOption('--plugin-name',
    dest = 'pluginName',
    type = 'string',
    nargs = 1,
    action = 'store',
    help = 'Full name of plugin')
AddOption('--plugin-id',
    dest = 'pluginId',
    type = 'string',
    nargs = 1,
    action = 'store',
    help = 'Unique 4 character ID code for plugin')
AddOption('--plugin-manuf',
    dest = 'pluginManufacturer',
    type = 'string',
    nargs = 1,
    action = 'store',
    help = 'Plugin manufacturer name')

pluginName = GetOption('pluginName')
pluginId = GetOption('pluginId')
pluginManufacturer = GetOption('pluginManufacturer')
PluginCoreEnv.Append(CCFLAGS = ["-DPLUGIN_NAME=" + str(pluginName),
    "-DPLUGIN_ID='" + str(pluginId) + "'",
    "-DPLUGIN_MANUFACTURER=" + str(pluginManufacturer)])

#if pluginName == None:
  #raise StopError, "Plugin name undefined, see help for details"
#elif pluginId == None:
  #raise StopError, "Plugin ID undefined, see help for details"
#elif pluginManufacturer == None:
  #raise StopError, "Plugin manufacturer undefined, see help for details"

if int(ARGUMENTS.get('debug', 0)):
  PluginCoreEnv.Append(CCFLAGS = ['-DDEBUG=1'])

Export('PluginCoreEnv')
SConscript(['source/SConscript', 'test/SConscript'])
