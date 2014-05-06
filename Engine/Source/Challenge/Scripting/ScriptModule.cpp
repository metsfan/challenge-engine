#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptModule.h>
#include <Challenge/Scripting/ScriptEngine.h>
#include <Challenge/Scripting/ScriptFunction.h>
#include <Challenge/Disk/Directory.h>

namespace challenge
{
	ScriptModule::ScriptModule(const std::string &name) :
		mName(name),
		mModule(NULL)
	{
		mScriptBuilder.StartNewModule(ScriptEngine::GetASEngine(), name.c_str());
	}

	ScriptModule::~ScriptModule()
	{
		if (mModule) {
			mEngine->GetASEngine()->DiscardModule(mName.c_str());
		}
	}

	void ScriptModule::AddFile(const std::string &file)
	{
		mScriptBuilder.AddSectionFromFile(file.c_str());
	}

	void ScriptModule::AddCode(const std::string &name, const TByteArray &code)
	{
		mScriptBuilder.AddSectionFromMemory(name.c_str(), (const char *) &code[0], code.size());
	}

	void ScriptModule::AddDirectory(const std::wstring &directory)
	{
		Directory dir(directory);
		auto &list = dir.GetFilesList();
		for (std::wstring &file : list) {
			this->AddFile(file);
		}
	}

	void ScriptModule::Build()
	{
		mScriptBuilder.BuildModule();
		mModule = ScriptEngine::GetASEngine()->GetModule(mName.c_str());
	}

	ScriptFunction * ScriptModule::GetFunction(const std::string &decl)
	{
		std::lock_guard<std::mutex> lock(mFunctionLock);

		if (!mModule) {
			return NULL;
		}

		size_t threadId = std::this_thread::get_id().hash();
		auto &bucket = mFunctions[threadId];

		auto it = bucket.find(decl);
		if (it != bucket.end()) {
			return it->second;
		}

		ScriptFunction *newFunction = new ScriptFunction(this, decl);
		bucket[decl] = newFunction;

		return newFunction;
	}
}