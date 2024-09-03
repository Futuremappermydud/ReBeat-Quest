#pragma once

#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/Sprite.hpp"

namespace ReBeat::Helpers
{
    class TextureHelper
    {
        public:
        static UnityEngine::Texture2D* DuplicateTexture(UnityEngine::Sprite* source);
        static UnityEngine::Texture2D* MergeTextures(std::vector<UnityEngine::Texture2D*> textures);
    };
}