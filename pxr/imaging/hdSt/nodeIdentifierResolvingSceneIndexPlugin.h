//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
#ifndef PXR_IMAGING_HD_ST_NODE_IDENTIFIER_RESOLVING_SCENE_INDEX_PLUGIN_H
#define PXR_IMAGING_HD_ST_NODE_IDENTIFIER_RESOLVING_SCENE_INDEX_PLUGIN_H

#include "pxr/imaging/hd/sceneIndexPlugin.h"
#include "pxr/pxr.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdSt_NodeIdentifierResolvingSceneIndexPlugin : public HdSceneIndexPlugin
{
public:
    HdSt_NodeIdentifierResolvingSceneIndexPlugin();
    ~HdSt_NodeIdentifierResolvingSceneIndexPlugin() override;

protected: // HdSceneIndexPlugin overrides
    HdSceneIndexBaseRefPtr _AppendSceneIndex(
        const HdSceneIndexBaseRefPtr& inputScene,
        const HdContainerDataSourceHandle& inputArgs) override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif