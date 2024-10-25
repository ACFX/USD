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

#ifndef PXR_IMAGING_HD_LEGACY_DISPLAY_STYLE_SCHEMA_H
#define PXR_IMAGING_HD_LEGACY_DISPLAY_STYLE_SCHEMA_H

/// \file

#include "pxr/imaging/hd/api.h"

#include "pxr/imaging/hd/schema.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

// --(BEGIN CUSTOM CODE: Declares)--
// --(END CUSTOM CODE: Declares)--

#define HD_LEGACY_DISPLAY_STYLE_SCHEMA_TOKENS \
    (displayStyle) \
    (refineLevel) \
    (flatShadingEnabled) \
    (displacementEnabled) \
    (occludedSelectionShowsThrough) \
    (pointsShadingEnabled) \
    (materialIsFinal) \
    (shadingStyle) \
    (reprSelector) \
    (cullStyle) \

TF_DECLARE_PUBLIC_TOKENS(HdLegacyDisplayStyleSchemaTokens, HD_API,
    HD_LEGACY_DISPLAY_STYLE_SCHEMA_TOKENS);

//-----------------------------------------------------------------------------


class HdLegacyDisplayStyleSchema : public HdSchema
{
public:
    /// \name Schema retrieval
    /// @{

    HdLegacyDisplayStyleSchema(HdContainerDataSourceHandle container)
      : HdSchema(container) {}

    /// Retrieves a container data source with the schema's default name token
    /// "displayStyle" from the parent container and constructs a
    /// HdLegacyDisplayStyleSchema instance.
    /// Because the requested container data source may not exist, the result
    /// should be checked with IsDefined() or a bool comparison before use.
    HD_API
    static HdLegacyDisplayStyleSchema GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer);

    /// @}

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

    /// \name Member accessor
    /// @{

    HD_API
    HdIntDataSourceHandle GetRefineLevel() const;

    HD_API
    HdBoolDataSourceHandle GetFlatShadingEnabled() const;

    HD_API
    HdBoolDataSourceHandle GetDisplacementEnabled() const;

    HD_API
    HdBoolDataSourceHandle GetOccludedSelectionShowsThrough() const;

    HD_API
    HdBoolDataSourceHandle GetPointsShadingEnabled() const;

    HD_API
    HdBoolDataSourceHandle GetMaterialIsFinal() const;

    HD_API
    HdTokenDataSourceHandle GetShadingStyle() const;

    HD_API
    HdTokenArrayDataSourceHandle GetReprSelector() const;

    HD_API
    HdTokenDataSourceHandle GetCullStyle() const; 

    /// @}

    /// \name Schema location
    /// @{

    /// Returns a token where the container representing this schema is found in
    /// a container by default.
    HD_API
    static const TfToken &GetSchemaToken();

    /// Returns an HdDataSourceLocator (relative to the prim-level data source)
    /// where the container representing this schema is found by default.
    HD_API
    static const HdDataSourceLocator &GetDefaultLocator();

    /// @}

    /// \name Data source locators for members
    ///
    /// The following methods return an HdDataSourceLocator (relative to the
    /// prim-level data source) where the data source for a member can be found.
    ///
    /// This is often useful for checking intersection against the
    /// HdDataSourceLocatorSet sent with HdDataSourceObserver::PrimsDirtied.
    /// @{

    /// Prim-level relative data source locator to locate reprSelector.
    HD_API
    static const HdDataSourceLocator &GetReprSelectorLocator();

    /// Prim-level relative data source locator to locate cullStyle.
    HD_API
    static const HdDataSourceLocator &GetCullStyleLocator();
    /// @} 

    /// \name Schema construction
    /// @{

    /// \deprecated Use Builder instead.
    ///
    /// Builds a container data source which includes the provided child data
    /// sources. Parameters with nullptr values are excluded. This is a
    /// low-level interface. For cases in which it's desired to define
    /// the container with a sparse set of child fields, the Builder class
    /// is often more convenient and readable.
    HD_API
    static HdContainerDataSourceHandle
    BuildRetained(
        const HdIntDataSourceHandle &refineLevel,
        const HdBoolDataSourceHandle &flatShadingEnabled,
        const HdBoolDataSourceHandle &displacementEnabled,
        const HdBoolDataSourceHandle &occludedSelectionShowsThrough,
        const HdBoolDataSourceHandle &pointsShadingEnabled,
        const HdBoolDataSourceHandle &materialIsFinal,
        const HdTokenDataSourceHandle &shadingStyle,
        const HdTokenArrayDataSourceHandle &reprSelector,
        const HdTokenDataSourceHandle &cullStyle
    );

    /// \class HdLegacyDisplayStyleSchema::Builder
    /// 
    /// Utility class for setting sparse sets of child data source fields to be
    /// filled as arguments into BuildRetained. Because all setter methods
    /// return a reference to the instance, this can be used in the "builder
    /// pattern" form.
    class Builder
    {
    public:
        HD_API
        Builder &SetRefineLevel(
            const HdIntDataSourceHandle &refineLevel);
        HD_API
        Builder &SetFlatShadingEnabled(
            const HdBoolDataSourceHandle &flatShadingEnabled);
        HD_API
        Builder &SetDisplacementEnabled(
            const HdBoolDataSourceHandle &displacementEnabled);
        HD_API
        Builder &SetOccludedSelectionShowsThrough(
            const HdBoolDataSourceHandle &occludedSelectionShowsThrough);
        HD_API
        Builder &SetPointsShadingEnabled(
            const HdBoolDataSourceHandle &pointsShadingEnabled);
        HD_API
        Builder &SetMaterialIsFinal(
            const HdBoolDataSourceHandle &materialIsFinal);
        HD_API
        Builder &SetShadingStyle(
            const HdTokenDataSourceHandle &shadingStyle);
        HD_API
        Builder &SetReprSelector(
            const HdTokenArrayDataSourceHandle &reprSelector);
        HD_API
        Builder &SetCullStyle(
            const HdTokenDataSourceHandle &cullStyle);

        /// Returns a container data source containing the members set thus far.
        HD_API
        HdContainerDataSourceHandle Build();

    private:
        HdIntDataSourceHandle _refineLevel;
        HdBoolDataSourceHandle _flatShadingEnabled;
        HdBoolDataSourceHandle _displacementEnabled;
        HdBoolDataSourceHandle _occludedSelectionShowsThrough;
        HdBoolDataSourceHandle _pointsShadingEnabled;
        HdBoolDataSourceHandle _materialIsFinal;
        HdTokenDataSourceHandle _shadingStyle;
        HdTokenArrayDataSourceHandle _reprSelector;
        HdTokenDataSourceHandle _cullStyle;

    };

    /// @}
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif