////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     SinkNode.h (nodes)
//  Authors:  Lisa Ong
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// model
#include "CompilableNode.h"
#include "IRMapCompiler.h"
#include "ModelTransformer.h"

// emitters
#include "IRMetadata.h"

// stl
#include <functional>
#include <string>
#include <vector>

namespace ell
{
namespace nodes
{
    /// <summary> A function that the SinkNode calls to deliver data to user code. </summary>
    ///
    /// In device-side compiled code, the function signature should be:
    /// ```
    /// void SinkFunction(ValueType* data)
    /// ```
    template <typename ValueType>
    using SinkFunction = std::function<void(const std::vector<ValueType>&)>;

    using OutputShape = ell::math::TensorShape;

    template <typename ValueType>
    class SinkNode : public model::CompilableNode
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* inputPortName = "input";
        static constexpr const char* outputPortName = "output";
        const model::InputPort<ValueType>& input = _input;
        const model::OutputPort<ValueType>& output = _output; // maybe we don't need this because results are reported via callback
        /// @}

        SinkNode();

        /// <summary> Constructor. </summary>
        ///
        /// <param name="input"> Port elements for input values. </param>
        /// <param name="sinkFunctionName"> The sink function name to be emitted. </param>
        /// <param name="sink"> The optional sink function that will receive output values. </param>
        SinkNode(const model::PortElements<ValueType>& input, const std::string& sinkFunctionName, SinkFunction<ValueType> sink = nullptr);

        /// <summary> Constructor. </summary>
        ///
        /// <param name="input"> Port elements for input values. </param>
        /// <param name="shape"> The output shape. </param>
        /// <param name="sinkFunctionName"> The sink function name to be emitted. </param>
        /// <param name="sink"> The optional sink function that will receive output values. </param>
        SinkNode(const model::PortElements<ValueType>& input, const OutputShape& shape, const std::string& sinkFunctionName, SinkFunction<ValueType> sink = nullptr);

        /// <summary> Constructor. </summary>
        ///
        /// <param name="input"> Port elements for input values. </param>
        /// <param name="outputVectorSize"> The output vector size. </param>
        /// <param name="sinkFunctionName"> The sink function name to be emitted. </param>
        /// <param name="sink"> The optional sink function that will receive output values. </param>
        SinkNode(const model::PortElements<ValueType>& input, size_t outputVectorSize, const std::string& sinkFunctionName, SinkFunction<ValueType> sink = nullptr);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("SinkNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Makes a copy of this node in the model being constructed by the transformer. </summary>
        ///
        /// <param name="transformer"> The `ModelTransformer` receiving the copy. </param>
        void Copy(model::ModelTransformer& transformer) const override;

        /// <summary> Sets the sink function for this node for use in Compute(). </summary>
        ///
        /// <param name="function"> The sink function to set. </param>
        void SetSinkFunction(SinkFunction<ValueType> function) { _sink = function; }
        
    protected:
        void Compute() const override;
        void Compile(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;

        // Evaluates whether the input meets the filter criteria,
        // and should be forwarded to the sink function.
        virtual bool EvaluateInput() const;

        utilities::ArchiveVersion GetArchiveVersion() const override;
        bool CanReadArchiveVersion(const utilities::ArchiveVersion& version) const override;
        void WriteToArchive(utilities::Archiver& archiver) const override;
        void ReadFromArchive(utilities::Unarchiver& archiver) override;
        bool HasState() const override { return true; } // stored state: callback function name, shape

    private:
        void SetOutputValuesLoop(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);
        void SetOutputValuesExpanded(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);
        void SetShape(const OutputShape& shape);
        OutputShape GetShape() const { return _shape; }

    private:
        model::InputPort<ValueType> _input;
        model::OutputPort<ValueType> _output;
        OutputShape _shape;

        std::string _sinkFunctionName;
        SinkFunction<ValueType> _sink;
    };
}
}

#include "../tcc/SinkNode.tcc"