////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     OutputNodeBase.h (model)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CompilableNode.h"
#include "CompilableNodeUtilities.h"
#include "ModelTransformer.h"
#include "Node.h"
#include "OutputPort.h"

// math
#include "TensorShape.h"

// utilities
#include "IArchivable.h"

// stl
#include <memory>
#include <string>
#include <vector>

namespace ell
{
/// <summary> model namespace </summary>
namespace model
{
    class IRMapCompiler;
    using OutputShape = ell::math::TensorShape;

    /// <summary> A node that represents an output from the system. </summary>
    class OutputNodeBase : public CompilableNode
    {
    public:
        const InputPortBase& GetInputPort() const { return _inputBase; }
        const OutputPortBase& GetOutputPort() const { return _outputBase; }
        using Node::GetInputPort;
        using Node::GetOutputPort;

        OutputShape GetShape() const { return _shape; }

    protected:
        OutputNodeBase(InputPortBase& input, OutputPortBase& output, ell::math::TensorShape shape);
        virtual bool ShouldCompileInline() const override { return true; }
        virtual bool HasState() const override { return false; }
        virtual void Compile(IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;
        virtual ell::utilities::ArchiveVersion GetArchiveVersion() const override;

        void SetShape(const OutputShape& shape) { _shape = shape; }
    private:
        InputPortBase& _inputBase;
        OutputPortBase& _outputBase;
        OutputShape _shape;
    };

}
}
