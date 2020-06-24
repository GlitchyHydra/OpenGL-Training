#pragma once

#include <string>

namespace My_OpenGL {

	class CubemapTexture
	{
	public:
		CubemapTexture(
			const std::string& Directory,
			const std::string& PosXFilename,
			const std::string& NegXFilename,
			const std::string& PosYFilename,
			const std::string& NegYFilename,
			const std::string& PosZFilename,
			const std::string& NegZFilename
		);
		~CubemapTexture();
	};

};