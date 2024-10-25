//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
////////////////////////////////////////////////////////////////////////

/* ************************************************************************** */
/* **                                                                      ** */
/* ** This file is generated by a script.                                  ** */
/* **                                                                      ** */
/* ** Do not edit it directly (unless it is within a CUSTOM CODE section)! ** */
/* ** Edit hdSchemaDefs.py instead to make changes.                        ** */
/* **                                                                      ** */
/* ************************************************************************** */

#include "pxr/imaging/hd/dependencySchema.h"

#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdDependencySchemaTokens,
    HD_DEPENDENCY_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdPathDataSourceHandle
HdDependencySchema::GetDependedOnPrimPath() const
{
    return _GetTypedDataSource<HdPathDataSource>(
        HdDependencySchemaTokens->dependedOnPrimPath);
}

HdLocatorDataSourceHandle
HdDependencySchema::GetDependedOnDataSourceLocator() const
{
    return _GetTypedDataSource<HdLocatorDataSource>(
        HdDependencySchemaTokens->dependedOnDataSourceLocator);
}

HdLocatorDataSourceHandle
HdDependencySchema::GetAffectedDataSourceLocator() const
{
    return _GetTypedDataSource<HdLocatorDataSource>(
        HdDependencySchemaTokens->affectedDataSourceLocator);
}

/*static*/
HdContainerDataSourceHandle
HdDependencySchema::BuildRetained(
        const HdPathDataSourceHandle &dependedOnPrimPath,
        const HdLocatorDataSourceHandle &dependedOnDataSourceLocator,
        const HdLocatorDataSourceHandle &affectedDataSourceLocator
)
{
    TfToken _names[3];
    HdDataSourceBaseHandle _values[3];

    size_t _count = 0;

    if (dependedOnPrimPath) {
        _names[_count] = HdDependencySchemaTokens->dependedOnPrimPath;
        _values[_count++] = dependedOnPrimPath;
    }

    if (dependedOnDataSourceLocator) {
        _names[_count] = HdDependencySchemaTokens->dependedOnDataSourceLocator;
        _values[_count++] = dependedOnDataSourceLocator;
    }

    if (affectedDataSourceLocator) {
        _names[_count] = HdDependencySchemaTokens->affectedDataSourceLocator;
        _values[_count++] = affectedDataSourceLocator;
    }
    return HdRetainedContainerDataSource::New(_count, _names, _values);
}

HdDependencySchema::Builder &
HdDependencySchema::Builder::SetDependedOnPrimPath(
    const HdPathDataSourceHandle &dependedOnPrimPath)
{
    _dependedOnPrimPath = dependedOnPrimPath;
    return *this;
}

HdDependencySchema::Builder &
HdDependencySchema::Builder::SetDependedOnDataSourceLocator(
    const HdLocatorDataSourceHandle &dependedOnDataSourceLocator)
{
    _dependedOnDataSourceLocator = dependedOnDataSourceLocator;
    return *this;
}

HdDependencySchema::Builder &
HdDependencySchema::Builder::SetAffectedDataSourceLocator(
    const HdLocatorDataSourceHandle &affectedDataSourceLocator)
{
    _affectedDataSourceLocator = affectedDataSourceLocator;
    return *this;
}

HdContainerDataSourceHandle
HdDependencySchema::Builder::Build()
{
    return HdDependencySchema::BuildRetained(
        _dependedOnPrimPath,
        _dependedOnDataSourceLocator,
        _affectedDataSourceLocator
    );
} 

PXR_NAMESPACE_CLOSE_SCOPE