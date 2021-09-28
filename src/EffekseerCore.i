%module EffekseerCore

%{

#include "../Core/EffekseerBackendCore.h"
#include "../Core/EffekseerEffectCore.h"
#include "../Core/EffekseerManagerCore.h"
#include "../Core/EffekseerNodeCore.h"

%}

%include "stdint.i"

#if SWIGJAVA
%include "swig/Lib/java/char16.i"
%include various.i
%apply char *BYTE { char* data };

%include "arrays_java.i"

%include "std_array.i"
%include "std_vector.i"
%include "std_auto_ptr.i"
%include "std_common.i"
%include "carrays.i"
%include "typemaps.i"
%include "stl.i"

%include "java.swg"
%include "enums.swg"

#endif

#if SWIGCSHARP
%include "swig/Lib/csharp/char16.i"
%include "arrays_csharp.i"

%apply unsigned char INPUT[] { const unsigned char* data };

#endif


#ifdef SWIGPYTHON
%begin %{
#define SWIG_PYTHON_STRICT_BYTE_CHAR
%}
%include "swig/Lib/python/char16.i"

 #endif

%include "cpp/Core/EffekseerBackendCore.h"
%include "cpp/Core/EffekseerEffectCore.h"
%include "cpp/Core/EffekseerManagerCore.h"
%include "cpp/Core/EffekseerNodeCore.h"