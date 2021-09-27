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

# build cpp dll
os.chdir('../')
os.makedirs('build/', exist_ok=True)
os.chdir('build')
call('cmake -A x64 -D BUILD_DX12=OFF -D BUILD_EXAMPLES=OFF ..')
call('cmake --build . --config Release')
shutil.copy('src/cpp/Release/EffekseerNativeForJava.dll',
            '../examples/libGdxSample/core/assets/EffekseerNativeForJava.dll')

#os.chdir(os.path.dirname(os.path.abspath(__file__)))

# generate java source files from swig from cpp
os.chdir('../src/')
call('generate_swig_wrapper.bat')

# build java classes and jar
os.chdir('java/')
call('ant build')

shutil.copy('../build_java/Effekseer.jar',
            '../../examples/libGdxSample/core/libs/Effekseer.jar')
