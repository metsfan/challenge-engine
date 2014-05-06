#pragma once

#include <Challenge/Challenge.h>
#include <angelscript/angelscript.h>
#include <angelscript/scriptbuilder/scriptbuilder.h>

namespace challenge
{
	class ScriptEngine;
	class ScriptFunction;

	static const std::wstring kDefaultScriptDirectory = L"Scripts";

	class ScriptModule
	{
		friend class ScriptEngine;
		friend class ScriptFunction;

	public:
		~ScriptModule();

		void AddFile(const std::string &file);
		void AddFile(const std::wstring &file)
		{
			this->AddFile(StringUtil::ToNarrow(file));
		}

		void AddCode(const std::string &name, const TByteArray &code);
		void AddDirectory(const std::wstring &directory);
		void AddDefaultScriptsDirectory()
		{
			this->AddDirectory(kDefaultScriptDirectory);
		}

		void Build();

		ScriptFunction * GetFunction(const std::string &decl);

	private:
		ScriptEngine *mEngine;
		asIScriptModule *mModule;
		CScriptBuilder mScriptBuilder;
		std::string mName;
		std::map<size_t, std::unordered_map<std::string, ScriptFunction *>> mFunctions;
		std::mutex mFunctionLock;

		ScriptModule(const std::string &name);

		asIScriptModule * GetModule() { return mModule; }
		ScriptEngine * GetEngine() { return mEngine; }
	};
};

