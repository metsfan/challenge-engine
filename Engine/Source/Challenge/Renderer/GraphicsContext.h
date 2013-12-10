#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shader/Shader.h>
#include <Challenge/Renderer/Shader/ShaderProgram.h>

namespace challenge
{
	class IShaderProgram;
	class IShader;
	class ITechnique;
	class ITexture;
	class Effect;

	typedef std::map<std::string, IShader *> TShaderCacheMap;
	typedef std::map<std::string, IShaderProgram *> TShaderProgramCacheMap;
	typedef std::map<std::string, Effect *> TEffectCacheMap;

	class IGraphicsContext
	{
	public:
		virtual void AddShader(std::string key, IShader *shader) = 0;
		virtual IShader* GetShader(std::string key) = 0;
		virtual bool ContainsShader(std::string key) = 0;

		virtual void AddShaderProgram(std::string key, IShaderProgram *program) = 0;
		virtual IShaderProgram* GetShaderProgram(std::string key) = 0;
		virtual bool ContainsShaderProgram(std::string key) = 0;

		virtual void AddEffect(std::string key, Effect *effect) = 0;
		virtual Effect* GetEffect(std::string key) = 0;
		virtual bool ContainsEffect(std::string key) = 0;

		virtual void SetActiveShaderProgram(IShaderProgram *shader) = 0;
	};

	class BaseGraphicsContext : public IGraphicsContext
	{
	public:
		BaseGraphicsContext();
		~BaseGraphicsContext();

		void AddShader(std::string key, IShader *shader);
		IShader* GetShader(std::string key);
		bool ContainsShader(std::string key) { return mShaders.count(key) != 0; }

		void AddShaderProgram(std::string key, IShaderProgram *program);
		IShaderProgram* GetShaderProgram(std::string key);
		bool ContainsShaderProgram(std::string key) { return mShaderPrograms.count(key) != 0; }

		void AddEffect(std::string key, Effect *effect);
		Effect* GetEffect(std::string key);
		bool ContainsEffect(std::string key) { return mEffects.count(key) != 0; }

		void SetActiveShaderProgram(IShaderProgram *shader);
		void SetActiveTexture(ITexture *texture, int slot);

	private:
		TShaderCacheMap mShaders;
		TShaderProgramCacheMap mShaderPrograms;
		TEffectCacheMap mEffects;
		IShaderProgram *mActiveShader;
		std::map<int, ITexture *> mActiveTextures;
	};

	template <typename Renderer>
	class GraphicsContext : public BaseGraphicsContext {};
};