////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     model.i (interfaces)
//  Authors:  Chuck Jacobs, Kirk Olynyk
//
////////////////////////////////////////////////////////////////////////////////////////////////////

%{
#include "ModelInterface.h"
%}

%include "ModelInterface.h"

#ifdef SWIGPYTHON
    %include "model_python_post.i"
#elif SWIGJAVASCRIPT
    %include "model_javascript_post.i"
#endif
