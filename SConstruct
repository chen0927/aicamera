import os
import sys
import rtconfig
import platform
import subprocess
import uuid

if os.path.exists('rt-thread'):
    RTT_ROOT = os.path.normpath(os.getcwd() + '/rt-thread')
else:
    RTT_ROOT = os.path.normpath(os.getcwd() + '../../../rt-thread')

sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
try:
    from building import *
except Exception as e:
    print("Error message:", e.message)
    print('Cannot found RT-Thread root directory, please check RTT_ROOT')
    print(RTT_ROOT)
    sys.exit(-1)

TARGET = 'rtthread.' + rtconfig.TARGET_EXT

DefaultEnvironment(tools=[])
env = Environment(tools = ['mingw'],
    AS = rtconfig.AS, ASFLAGS = rtconfig.AFLAGS,
    CC = rtconfig.CC, CFLAGS = rtconfig.CFLAGS,
    CXX = rtconfig.CXX, CXXFLAGS = rtconfig.CXXFLAGS,
    AR = rtconfig.AR, ARFLAGS = '-rc',
    LINK = rtconfig.LINK, LINKFLAGS = rtconfig.LFLAGS)
env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

if rtconfig.PLATFORM in ['iccarm']:
    env.Replace(CCCOM = ['$CC $CFLAGS $CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS -o $TARGET $SOURCES'])
    env.Replace(ARFLAGS = [''])
    env.Replace(LINKCOM = env["LINKCOM"] + ' --map project.map')

Export('RTT_ROOT')
Export('rtconfig')

SDK_ROOT = os.path.abspath('./')
if os.path.exists(SDK_ROOT + '/libraries'):
    libraries_path_prefix = SDK_ROOT + '/libraries'
else:
    libraries_path_prefix = os.path.dirname(SDK_ROOT) + '/../libraries'

SDK_LIB = libraries_path_prefix
Export('SDK_LIB')

rtconfig.BSP_LIBRARY_TYPE = None

# prepare building environment
objs = PrepareBuilding(env, RTT_ROOT, has_libcpu=False)

# set spawn
def ourspawn(sh, escape, cmd, args, e):
    filename = str(uuid.uuid4())
    newargs = ' '.join(args[1:])
    cmdline = cmd + " " + newargs
    if (len(cmdline) > 16 * 1024):
        f = open(filename, 'w')
        f.write(' '.join(args[1:]).replace('\\', '/'))
        f.close()
        # exec
        cmdline = cmd + " @" + filename
    proc = subprocess.Popen(cmdline, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
        stderr=subprocess.PIPE, shell = False, env = e)
    data, err = proc.communicate()
    rv = proc.wait()
    def res_output(_output, _s):
        if len(_s):
            if isinstance(_s, str):
                _output(_s)
            elif isinstance(_s, bytes):
                _output(str(_s, 'UTF-8'))
            else:
                _output(str(_s))
    res_output(sys.stderr.write, err)
    res_output(sys.stdout.write, data)
    if os.path.isfile(filename):
        os.remove(filename)
    return rv

# 解决env-scons不能链接长路径问题
if platform.system() == 'Windows':
    env['SPAWN'] = ourspawn

# include drivers
objs.extend(SConscript(os.path.join(libraries_path_prefix, 'HAL_Drivers', 'SConscript')))
# make a building
DoBuilding(TARGET, objs)
