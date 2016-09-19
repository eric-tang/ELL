////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     AddToAction.h (compile)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LinearOperation.h"

// layers
#include "Coordinate.h"

// stl
#include <string>
#include <iostream>

/// <summary> Encodes the operation: "variable_targetID += a*x + b". </summary>
class AddToAction
{
public:

    /// <summary> Constructs an instance of AddToAction. </summary>
    ///
    /// <param name="targetCoordinate"> The action's target coordinate. </param>
    AddToAction(layers::Coordinate targetCoordinate);

    /// <summary> Constructs an instance of AddToAction. </summary>
    ///
    /// <param name="operation"> The action's operation. </param>
    /// <param name="targetCoordinate"> The actions target coordinate. </param>
    AddToAction(const LinearOperation& operation, layers::Coordinate targetCoordinate);

    /// <summary> Gets the action's operation. </summary>
    ///
    /// <returns> The operation. </returns>
    const LinearOperation& GetOperation() const { return _operation; }

    /// <summary> Gets the action's target coordinate. </summary>
    ///
    /// <returns> The target coordinate. </returns>
    const layers::Coordinate& GetTarget() const { return _targetCoordinate; }

    /// <summary> Query if this action is a null action (a null action does not change its target). </summary>
    ///
    /// <returns> true if the action is a null action. </returns>
    bool IsNull() const { return _operation.IsNull(); }

private:
    LinearOperation _operation;
    layers::Coordinate _targetCoordinate;
};