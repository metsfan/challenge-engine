#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shader/Shader.h>
#include <Challenge/Renderer/Shader/ShaderProgram.h>
#include <Challenge/Renderer/GraphicsDevice.h>

namespace challenge
{
	void BaseShader::AddGlobalVariable(uint32_t index, const std::string &name,
		const std::string &semantic, ShaderVarType type, int num)
	{
		int numVars = this->GetDevice()->GetContext()->GetNumGlobalVariables();
		if (numVars != mGlobalVars.size()) {
			mGlobalVars.resize(numVars);
		}
		//mGlobalVars.push_back(ShaderGlobalVar());

		ShaderGlobalVar &var = mGlobalVars[index];
		var.globalId = index;
		var.localId = this->GetVariableLocalIndex(name);
		var.name = name;
		var.semantic = semantic;
		var.type = type;
		var.size = ShaderVarSizes[type];
		var.num = num;

		mGlobalIndices.push_back(index);
	}

	int32_t BaseShader::GetVariableIndex(const std::string &semantic)
	{
		int i = 0;
		for (auto &var : mGlobalVars) {
			if (var.semantic == semantic) {
				return i;
			}

			i++;
		}

		return -1;
	}

	void BaseShader::UpdateState(IShaderProgram *program, RenderState &state)
	{
		for (int i = 0; i < mGlobalIndices.size(); i++) {
			ShaderGlobalVar &var = mGlobalVars[mGlobalIndices[i]];
			
			void *data = state.GetShaderData(var.globalId);
			if (data) {
				if (var.type == ShaderVarTexture) {
					ITexture *texture = reinterpret_cast<ITexture *>(data);
					program->SetTexture(0, texture, mType);
				}
				else {
					program->SetConstantDataStruct(var.localId, data, var.size * var.num, mType);
				}
				
			}
		}
	}
}
