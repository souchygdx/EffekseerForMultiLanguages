
setlocal enableextensions

rmdir /s /q java\\effekseer
rmdir /s /q build_java
mkdir java\\effekseer\\swig
::mkdir csharp\\swig
::mkdir python\\swig

mkdir cpp\\java
::mkdir cpp\\csharp
::mkdir cpp\\python
endlocal

swig -c++ -java -package effekseer.swig -o cpp/java/dll.cpp -outdir java/effekseer/swig/ EffekseerCore.i
::swig -c++ -csharp -namespace Effekseer.swig -o cpp/csharp/dll.cpp -outdir csharp/swig/ -dllimport EffekseerNativeForCSharp EffekseerCore.i
::swig -c++ -python -o cpp/python/dll.cpp -outdir python/swig/ EffekseerCore.i

