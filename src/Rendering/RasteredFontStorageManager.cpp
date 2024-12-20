#include "RasteredFontStorageManager.h"
#include "FontRaster.h"
#include <algorithm>

RasteredFontStorageSharedPtr RasteredFontStorageManager::getRasteredFontStorage(const RasteredFontStoragePreset& preset)
{
	const size_t key = hashFontPreset(preset);
	if (auto it = _rasteredFontStorages.find(key); it != _rasteredFontStorages.end())
	{
		return it->second;
	}

	FontRasterSharedPtr fontRaster = std::make_shared<FontRaster>(preset.fontPath);
	RasteredFontStorageSharedPtr rasteredFontStorage = std::make_shared<RasteredFontStorage>(fontRaster, preset.charRangeSize);
	rasteredFontStorage->setFontSize(preset.fontWidth, preset.fontHeight);
	_rasteredFontStorages[key] = rasteredFontStorage;
	return rasteredFontStorage;
}

size_t RasteredFontStorageManager::hashFontPreset(const RasteredFontStoragePreset& preset) const
{
	std::hash<std::string> hasher;
	return hasher(
		preset.fontPath.string() +
		std::to_string(preset.fontWidth) +
		std::to_string(preset.fontHeight)
	);
}
