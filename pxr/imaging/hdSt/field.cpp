//
// Copyright 2016 Pixar
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
#include "pxr/imaging/hdSt/field.h"
#include "pxr/imaging/hdSt/resourceRegistry.h"

#include "pxr/imaging/hd/volume.h"
#include "pxr/imaging/hd/sceneDelegate.h"
#include "pxr/imaging/glf/textureRegistry.h"
#include "pxr/imaging/glf/textureHandle.h"
#include "pxr/imaging/glf/vdbTexture.h"
#include "pxr/imaging/glf/vdbTextureContainer.h"

#include "pxr/usd/sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(
    _tokens,
    (fieldName)
);

HdStField::HdStField(SdfPath const& id, TfToken const & fieldType) 
  : HdField(id)
  , _fieldType(fieldType)
  , _isInitialized(false)
{
}

HdStField::~HdStField() = default;

// Obtain texture handle for grid with name fieldName in OpenVDB file at
// given path.
static
GlfTextureHandleRefPtr
_GetVdbTexture(std::string const &path,
               TfToken const &fieldName)
{
    // First query the texture registry for the texture container for
    // the OpenVDB file.
    GlfTextureHandleRefPtr const containerHandle = 
        GlfTextureRegistry::GetInstance().GetTextureHandle(
            TfToken(path));
    if (!containerHandle) {
        return TfNullPtr;
    }
    
    GlfVdbTextureContainerPtr const container =
        TfDynamic_cast<GlfVdbTextureContainerPtr>(
            containerHandle->GetTexture());
    if (!container) {
        TF_CODING_ERROR("When trying to create texture for VDB grid, "
                        "texture handle does not contain vdb texture "
                        "container.");
        return TfNullPtr;
    }

    // Then get the texture handle from the container.
    return container->GetTextureHandle(fieldName);
}

void
HdStField::Sync(HdSceneDelegate *sceneDelegate,
                HdRenderParam   *renderParam,
                HdDirtyBits     *dirtyBits)
{
    // This code is similar to HdTexture::Sync.
    if (*dirtyBits & DirtyParams) {

        // Get asset path from scene delegate.
        //
        const VtValue filePath = sceneDelegate->Get(GetId(),
                                                    HdFieldTokens->filePath);
        const SdfAssetPath fileAssetPath = filePath.Get<SdfAssetPath>();

        const VtValue fieldNameValue = sceneDelegate->Get(GetId(),
                                                          _tokens->fieldName);
        const TfToken fieldName = fieldNameValue.Get<TfToken>();

        // Resolve asset path
        //
        // Assuming that correct resolve context is set when HdStField::Sync is
        // called.
        const std::string &resolvedPath = fileAssetPath.GetResolvedPath();

        // Using resolved path and field name for key
        size_t hash = 0;
        boost::hash_combine(hash, resolvedPath);
        boost::hash_combine(hash, fieldName);
        HdResourceRegistry::TextureKey texID = hash;

        // Note that unlike HdTexture::Sync, we do not use
        // renderIndex.GetTextureKey(texID) to convert a local texture id
        // into a global texture key.
        // That way, a field resource is shared accross different render
        // indices/delegates.

        HdRenderIndex &renderIndex = sceneDelegate->GetRenderIndex();

        HdStResourceRegistrySharedPtr const &resourceRegistry =
            std::static_pointer_cast<HdStResourceRegistry>(
                renderIndex.GetResourceRegistry());

        // Check with resource registry whether the field resource
        // for this file has already been created.
        HdInstance<HdStTextureResourceSharedPtr> texInstance =
                resourceRegistry->RegisterTextureResource(texID);


        // Has the texture really changed.
        // The safest thing to do is assume it has, so that's the default used
        bool isNewTexture = true;

        if (texInstance.IsFirstInstance()) {
            // Get texture for respective grid in VDB file to create field
            // resource.
            //
            // Note that creating the field resource also does the necessary
            // OpenGL calls to create the sampler and (if bindless) the OpenGL
            // texture handle.
            // We have to do this here in the regLock scope since this Sync call
            // as well as the Sync call of the client HdStVolume are
            // concurrently with the Sync calls of other bprims or rprims.
            //
            // This is different from HdStMaterial that can create the OpenGL
            // sampler and texture handle in Sync without lock since it is an
            // sprim and is not run multi-threadedly.
            // 
            _fieldResource = std::make_shared<HdStFieldResource>(
                _GetVdbTexture(resolvedPath, fieldName));
            texInstance.SetValue(_fieldResource);
        } else {
            HdStFieldResourceSharedPtr const fieldResource =
                std::dynamic_pointer_cast<HdStFieldResource>(
                                                texInstance.GetValue());
            if (_fieldResource == fieldResource) {
                isNewTexture = false;
            } else {
                _fieldResource = fieldResource;
            }
        }

        // The texture resource may have been cleared, so we need to release the
        // old one.
        //
        // This is particularly important if the update is on the memory
        // request.
        // As the cache may be still holding on to the resource with a larger
        // memory request.
        if (isNewTexture) {
            renderIndex.GetChangeTracker().SetBprimGarbageCollectionNeeded();
        }

        if (_isInitialized) {
            // Force volume prim to pick up the new field resource and
            // recompute bounding box.
            //
            // XXX:-matthias
            // Ideally, this would be more fine-grained than blasting all
            // rprims.
            HdChangeTracker& changeTracker =
                sceneDelegate->GetRenderIndex().GetChangeTracker();
            changeTracker.MarkAllRprimsDirty(HdChangeTracker::DirtyVolumeField);
        }
    }

    _isInitialized = true;

    *dirtyBits = Clean;
}

HdDirtyBits 
HdStField::GetInitialDirtyBitsMask() const 
{
    return DirtyBits::AllDirty;
}

PXR_NAMESPACE_CLOSE_SCOPE
