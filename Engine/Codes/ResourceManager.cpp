#include "ResourceManager.h"
#include "GraphicManager.h"
#include "Texture.h"
#include "Animation.h"

using namespace Engine;

void Engine::ResourceManager::SetWICFactory(IWICImagingFactory* pWICFactory)
{
    _pWICFactory = pWICFactory;
}

bool Engine::ResourceManager::LoadTexture(int slashOffset, const wchar_t* filePath)
{
    _wfinddata_t fd;
    intptr_t handle;
    int result = 0;

    wchar_t rootPath[256] = L"";

    lstrcpy(rootPath, filePath);
    lstrcat(rootPath, L"/*");
    handle = _wfindfirst(rootPath, &fd);

    if (-1 != handle)
    {
        while (true)
        {
            result = _wfindnext(handle, &fd);

            if (-1 == result)
                break;

            if (!lstrcmp(L".", fd.name) || !lstrcmp(L"..", fd.name))
                continue;

            if (0 == result && fd.attrib & _A_SUBDIR)
            {
                int index = 0;
                wchar_t currPath[256] = L"";

                while ('*' != rootPath[index])
                {
                    currPath[index] = rootPath[index];
                    index++;
                }

                lstrcat(currPath, fd.name);
                LoadTexture(slashOffset, currPath);
                continue;
            }

            wchar_t textureTag[64] = L"";
            wchar_t newFilePath[256] = L"";

            lstrcpy(newFilePath, filePath);
            lstrcat(newFilePath, L"/");
            lstrcat(newFilePath, fd.name);

            int index = 0;
            int offset = 0;
            int length = lstrlen(filePath);

            while (slashOffset != offset)
            {
                if ('/' == filePath[index++])
                    offset++;
            }

            offset = index;
            index = 0;

            while (offset < length)
            {
                textureTag[index] = filePath[offset++];

                if (textureTag[index] == '/')
                    textureTag[index] = '_';

                index++;
            }

            Texture* pTexture = _textureData[textureTag];

            if (nullptr == pTexture)
            {
                pTexture = Texture::Create();
                _textureData[textureTag] = pTexture;
            }

            ID2D1Bitmap* pBitmap;
            CreateImage(GraphicManager::GetInstance()->GetRenderTarget(), newFilePath, &pBitmap);

            pTexture->AddIamge(pBitmap);
        }
    }

    return true;
}

bool Engine::ResourceManager::LoadAnimation(int slashOffset, const wchar_t* filePath)
{
    _wfinddata_t fd;
    intptr_t handle;
    int result = 0;

    wchar_t rootPath[256] = L"";

    lstrcpy(rootPath, filePath);
    lstrcat(rootPath, L"/*");
    handle = _wfindfirst(rootPath, &fd);

    if (-1 != handle)
    {
        while (true)
        {
            result = _wfindnext(handle, &fd);

            if (-1 == result)
                break;

            if (!lstrcmp(L".", fd.name) || !lstrcmp(L"..", fd.name))
                continue;

            if (0 == result && fd.attrib & _A_SUBDIR)
            {
                int index = 0;
                wchar_t currPath[256] = L"";

                while ('*' != rootPath[index])
                {
                    currPath[index] = rootPath[index];
                    index++;
                }

                lstrcat(currPath, fd.name);
                LoadAnimation(slashOffset, currPath);
                continue;
            }

            wchar_t animationTag[64] = L"";
            wchar_t newFilePath[256] = L"";

            lstrcpy(newFilePath, filePath);
            lstrcat(newFilePath, L"/");
            lstrcat(newFilePath, fd.name);

            int index = 0;
            int offset = 0;
            int length = lstrlen(newFilePath);

            while (slashOffset != offset)
            {
                if ('/' == filePath[index++])
                    offset++;
            }

            offset = index;
            index = 0;
            while (offset < length)
            {
                animationTag[index] = newFilePath[offset++];

                if ('.' == newFilePath[offset])
                    break;

                if (animationTag[index] == '/')
                    animationTag[index] = '_';

                index++;
            }

            CreateAnimation(newFilePath, animationTag);
        }
    }

    return true;
}

Texture* Engine::ResourceManager::FindTexture(const wchar_t* textureTag)
{
    return _textureData[textureTag];
}

ResourceManager::AnimationInfo Engine::ResourceManager::FindAnimation(const wchar_t* animationTag)
{
    return _animationData[animationTag];
}

void Engine::ResourceManager::Free()
{
    for (auto& Pair : _textureData)
        SafeRelease(Pair.second);
}

bool Engine::ResourceManager::CreateImage(ID2D1HwndRenderTarget* pRenderTarget, const wchar_t* filePath, ID2D1Bitmap** ppBitmap)
{
    HRESULT hr;
    
    IWICBitmapDecoder* pDecoder = nullptr;
    IWICFormatConverter* pConverter = nullptr;

    hr = _pWICFactory->CreateDecoderFromFilename(filePath, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);

    IWICBitmapFrameDecode* pFrame = nullptr;
    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    if (SUCCEEDED(hr))
    {
        hr = _pWICFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pFrame, 
            GUID_WICPixelFormat32bppPBGRA, 
            WICBitmapDitherTypeNone, 
            nullptr, 
            0.f, 
            WICBitmapPaletteTypeCustom);
    }

    if (SUCCEEDED(hr))
    {
        hr = pRenderTarget->CreateBitmapFromWicBitmap(pConverter, nullptr, ppBitmap);
    }

    if (FAILED(hr))
        *ppBitmap = nullptr;

    // 파일을 사용할때마다 다시 만든다.
    SafeRelease(pConverter);
    SafeRelease(pDecoder);
    SafeRelease(pFrame);

    return true;
}

bool Engine::ResourceManager::CreateAnimation(const wchar_t* filePath, const wchar_t* animationTag)
{
    std::wifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return false;
    }

    std::wstring line;
    std::getline(file, line);
    std::getline(file, line);

    int AnimationCount = 0;
    {
        std::wstringstream wss(line);
        wss >> AnimationCount;
    }

    for (int i = 0; i < AnimationCount; i++)
    {
        getline(file, line);
        std::wstringstream wss(line);
        std::wstring token;
        {
            getline(wss, token, L',');
            std::wstring animationName = token;
            getline(wss, token, L',');
            std::wstring TextureTag = token;
            getline(wss, token, L',');
            float duration = (float)_wtof(token.c_str());

            Texture* pTexture = FindTexture(TextureTag.c_str());

            if (nullptr == pTexture)
                return false;

            for (auto& Bitmap : pTexture->_imageData)
                _animationData[animationTag][animationName].push_back(Frame(Bitmap, 1.f / duration));
        }
    }

    return true;
}
