#include "Helpers/TextureHelper.hpp"

#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/Graphics.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Color.hpp"
#include "beatsaber-hook/shared/utils/typedefs-array.hpp"
#include <cmath>
#include <limits>

namespace ReBeat::Helpers
{
    UnityEngine::Texture2D* TextureHelper::DuplicateTexture(UnityEngine::Sprite* source)
    {
        float width = source->texture->width;
        float height = source->texture->height;
        float cropWidth = source->textureRect.width;
        float cropHeight = source->textureRect.height;
        float cropX = source->textureRect.x;
        float cropY = source->texture->height - source->textureRect.y - cropHeight;
        UnityEngine::RenderTexture* renderTex = UnityEngine::RenderTexture::GetTemporary(
            (int)width,
            (int)height,
            0,
            UnityEngine::RenderTextureFormat::Default,
            UnityEngine::RenderTextureReadWrite::Linear);

        UnityEngine::Graphics::Blit(source->texture, renderTex);
        UnityEngine::RenderTexture* previous = UnityEngine::RenderTexture::get_active();
        UnityEngine::RenderTexture::set_active(renderTex);

        UnityEngine::Texture2D* readableText = UnityEngine::Texture2D::New_ctor((int)cropWidth, (int)cropHeight);
        readableText->ReadPixels(UnityEngine::Rect(cropX, cropY, cropWidth, cropHeight), 0, 0);
        readableText->Apply();

        UnityEngine::RenderTexture::set_active(previous);
        UnityEngine::RenderTexture::ReleaseTemporary(renderTex);
        return readableText;
    }

    UnityEngine::Color LerpColor(UnityEngine::Color c1, UnityEngine::Color c2, float value) {
        return UnityEngine::Color(c1.r + (c2.r - c1.r) * value, c1.g + (c2.g - c1.g) * value, c1.b + (c2.b - c1.b) * value, c1.a + (c2.a - c1.a) * value);
    }

    ArrayW<UnityEngine::Color> ScaleTexture(UnityEngine::Texture2D* texture, int width, int height) {
        auto origColors = texture->GetPixels();
        ArrayW<UnityEngine::Color> destColors = ArrayW<UnityEngine::Color>(width * height);

        int origWidth = texture->width;
        float ratioX = (texture->width - 1) / (float)width;
        float ratioY = (texture->height - 1) / (float)height;

        for (int destY = 0; destY < height; destY++) {
            int origY = (int)(destY * ratioY);
            float yLerp = destY * ratioY - origY;

            float yIdx1 = origY * origWidth;
            float yIdx2 = (origY + 1) * origWidth;
            float yIdxDest = destY * width;

            for (int destX = 0; destX < width; destX++) {
                int origX = (int)(destX * ratioX);
                float xLerp = destX * ratioX - origX;
                destColors[(int)(yIdxDest + destX)] = LerpColor(
                    LerpColor(origColors[(int)(yIdx1 + origX)], origColors[(int)(yIdx1 + origX) + 1], xLerp),
                    LerpColor(origColors[(int)(yIdx2 + origX)], origColors[(int)(yIdx2 + origX) + 1], xLerp),
                    yLerp
                );
            }
        }
        return destColors;
    }

    int CalculateTotalWidth(std::vector<UnityEngine::Texture2D*> textures, int targetHeight) {
        int totalWidth = 0;
        for (auto texture : textures) {
            int width = std::round((float)targetHeight * texture->width / texture->height);
            totalWidth += width;
        }
        return totalWidth;
    }

    UnityEngine::Texture2D* TextureHelper::MergeTextures(std::vector<UnityEngine::Texture2D*> textures)
    {
        const int finalHeight = 512; // Fixed height of 512 pixels
        int totalWidth = CalculateTotalWidth(textures, finalHeight);

        UnityEngine::Texture2D* result = UnityEngine::Texture2D::New_ctor(totalWidth, finalHeight);
        ArrayW<UnityEngine::Color> finalColors = ArrayW<UnityEngine::Color>(totalWidth * finalHeight);

        int currentX = 0;
        for (auto texture : textures) {
            int width = std::round((float)finalHeight * texture->width / texture->height);
            int height = finalHeight;

            ArrayW<UnityEngine::Color> scaledTextureColors = ScaleTexture(texture, width, height);

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int destIndex = y * totalWidth + currentX + x;
                    if (destIndex < finalColors.size()) {
                        finalColors[destIndex] = scaledTextureColors[y * width + x];
                    }
                }
            }

            currentX += width;
        }

        result->SetPixels(finalColors);
        result->Apply();

        return result;
    }
}