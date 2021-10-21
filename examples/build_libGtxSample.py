import subprocess
import shutil
import os

# to call a process even if exe is bat (Windows)
def call( cmd , env=None):
    """ call command line.
    """

    print( cmd )
    p = subprocess.Popen(cmd, shell=True, env=env)
    ret = p.wait()
    if ret != 0:
        raise RuntimeError('failed command: "{}" with {}'.format(cmd, ret))
    print('')


os.chdir(os.path.dirname(os.path.abspath(__file__)))

# 
os.chdir('../')
os.makedirs('build/', exist_ok=True)

# build cpp EffekseerCore
os.chdir('build')
call('cmake -A x64 -D BUILD_DX12=OFF -D BUILD_EXAMPLES=OFF ..')

# generate dll.cpp and java source files with swig
os.chdir('../src/')
call('generate_swig_wrapper.bat')

#build NativeJava.dll from dll.cpp from swig
os.chdir('../build/')
call('cmake --build . --config Release')
shutil.copy('src/cpp/Release/EffekseerNativeForJava.dll',
            '../examples/libGdxSample/core/assets/EffekseerNativeForJava.dll')
shutil.copy('src/cpp/Release/EffekseerNativeForJava.dll',
            '../examples/Jeffekseer/EffekseerNativeForJava.dll')

# build java classes and jar
os.chdir('../src/java/')
call('ant build')

shutil.copy('../build_java/Effekseer.jar',
            '../../examples/libGdxSample/core/libs/Effekseer.jar')
