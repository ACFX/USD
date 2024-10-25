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

#include "pxr/imaging/hd/meshSchema.h"

#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdMeshSchemaTokens,
    HD_MESH_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdMeshTopologySchema
HdMeshSchema::GetTopology() const
{
    return HdMeshTopologySchema(_GetTypedDataSource<HdContainerDataSource>(
        HdMeshSchemaTokens->topology));
}

HdTokenDataSourceHandle
HdMeshSchema::GetSubdivisionScheme() const
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdMeshSchemaTokens->subdivisionScheme);
}

HdSubdivisionTagsSchema
HdMeshSchema::GetSubdivisionTags() const
{
    return HdSubdivisionTagsSchema(_GetTypedDataSource<HdContainerDataSource>(
        HdMeshSchemaTokens->subdivisionTags));
}

HdBoolDataSourceHandle
HdMeshSchema::GetDoubleSided() const
{
    return _GetTypedDataSource<HdBoolDataSource>(
        HdMeshSchemaTokens->doubleSided);
}

/*static*/
HdContainerDataSourceHandle
HdMeshSchema::BuildRetained(
        const HdContainerDataSourceHandle &topology,
        const HdTokenDataSourceHandle &subdivisionScheme,
        const HdContainerDataSourceHandle &subdivisionTags,
        const HdBoolDataSourceHandle &doubleSided
)
{
    TfToken _names[4];
    HdDataSourceBaseHandle _values[4];

    size_t _count = 0;

    if (topology) {
        _names[_count] = HdMeshSchemaTokens->topology;
        _values[_count++] = topology;
    }

    if (subdivisionScheme) {
        _names[_count] = HdMeshSchemaTokens->subdivisionScheme;
        _values[_count++] = subdivisionScheme;
    }

    if (subdivisionTags) {
        _names[_count] = HdMeshSchemaTokens->subdivisionTags;
        _values[_count++] = subdivisionTags;
    }

    if (doubleSided) {
        _names[_count] = HdMeshSchemaTokens->doubleSided;
        _values[_count++] = doubleSided;
    }
    return HdRetainedContainerDataSource::New(_count, _names, _values);
}

HdMeshSchema::Builder &
HdMeshSchema::Builder::SetTopology(
    const HdContainerDataSourceHandle &topology)
{
    _topology = topology;
    return *this;
}

HdMeshSchema::Builder &
HdMeshSchema::Builder::SetSubdivisionScheme(
    const HdTokenDataSourceHandle &subdivisionScheme)
{
    _subdivisionScheme = subdivisionScheme;
    return *this;
}

HdMeshSchema::Builder &
HdMeshSchema::Builder::SetSubdivisionTags(
    const HdContainerDataSourceHandle &subdivisionTags)
{
    _subdivisionTags = subdivisionTags;
    return *this;
}

HdMeshSchema::Builder &
HdMeshSchema::Builder::SetDoubleSided(
    const HdBoolDataSourceHandle &doubleSided)
{
    _doubleSided = doubleSided;
    return *this;
}

HdContainerDataSourceHandle
HdMeshSchema::Builder::Build()
{
    return HdMeshSchema::BuildRetained(
        _topology,
        _subdivisionScheme,
        _subdivisionTags,
        _doubleSided
    );
}

/*static*/
HdMeshSchema
HdMeshSchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdMeshSchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdMeshSchemaTokens->mesh))
        : nullptr);
}

/*static*/
const TfToken &
HdMeshSchema::GetSchemaToken()
{
    return HdMeshSchemaTokens->mesh;
}

/*static*/
const HdDataSourceLocator &
HdMeshSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(GetSchemaToken());
    return locator;
}

/* static */
const HdDataSourceLocator &
HdMeshSchema::GetTopologyLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdMeshSchemaTokens->topology);
    return locator;
}

/* static */
const HdDataSourceLocator &
HdMeshSchema::GetSubdivisionSchemeLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdMeshSchemaTokens->subdivisionScheme);
    return locator;
}

/* static */
const HdDataSourceLocator &
HdMeshSchema::GetSubdivisionTagsLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdMeshSchemaTokens->subdivisionTags);
    return locator;
}

/* static */
const HdDataSourceLocator &
HdMeshSchema::GetDoubleSidedLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdMeshSchemaTokens->doubleSided);
    return locator;
} 

PXR_NAMESPACE_CLOSE_SCOPE