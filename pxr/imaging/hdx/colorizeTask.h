//
// Copyright 2018 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_IMAGING_HDX_COLORIZE_TASK_H
#define PXR_IMAGING_HDX_COLORIZE_TASK_H

#include "pxr/pxr.h"
#include "pxr/imaging/hdx/api.h"
#include "pxr/imaging/hdx/fullscreenShader.h"
#include "pxr/imaging/hdx/progressiveTask.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdRenderBuffer;

/// \class HdxColorizeTask
///
/// A task for taking output AOV data and rendering it to the current
/// GL buffer, possibly with a "colorizing" step (for example, mapping
/// normals to RGB, or texture coords to RG).
///
class HdxColorizeTask : public HdxProgressiveTask
{
public:
    HDX_API
    HdxColorizeTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    virtual ~HdxColorizeTask();

    /// Hooks for progressive rendering.
    virtual bool IsConverged() const override;

    /// Sync the render pass resources
    HDX_API
    virtual void Sync(HdSceneDelegate* delegate,
                      HdTaskContext* ctx,
                      HdDirtyBits* dirtyBits) override;

    /// Prepare the colorize task
    HDX_API
    virtual void Prepare(HdTaskContext* ctx,
                         HdRenderIndex* renderIndex) override;

    /// Execute the colorize task
    HDX_API
    virtual void Execute(HdTaskContext* ctx) override;

private:
    // Incoming data
    TfToken _aovName;
    SdfPath _aovBufferPath;
    SdfPath _depthBufferPath;
    bool _applyColorQuantization;

    HdRenderBuffer *_aovBuffer;
    HdRenderBuffer *_depthBuffer;

    // Ouptut data
    uint8_t *_outputBuffer;
    size_t _outputBufferSize;
    bool _converged;

    HdxFullscreenShader _compositor;
    bool _needsValidation;

    HdxColorizeTask() = delete;
    HdxColorizeTask(const HdxColorizeTask &) = delete;
    HdxColorizeTask &operator =(const HdxColorizeTask &) = delete;
};

/// \class HdxColorizeTaskParams
///
/// ColorizeTask parameters.
///
struct HdxColorizeTaskParams
{
    HdxColorizeTaskParams()
        : aovName()
        , aovBufferPath()
        , depthBufferPath()
        , applyColorQuantization(false)
        {}

    // XXX: Right now the API is pretty basic: draw buffer X as aov Y
    // (e.g., colorize this buffer as float3 normals).  Lots of room for
    // cool improvements here!
    TfToken aovName;
    SdfPath aovBufferPath;
    SdfPath depthBufferPath;
    bool applyColorQuantization;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxColorizeTaskParams& pv);
HDX_API
bool operator==(const HdxColorizeTaskParams& lhs,
                const HdxColorizeTaskParams& rhs);
HDX_API
bool operator!=(const HdxColorizeTaskParams& lhs,
                const HdxColorizeTaskParams& rhs);

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_IMAGING_HDX_COLORIZE_TASK_H
