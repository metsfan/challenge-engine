#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptObject.h>

#include <angelscript/angelscript.h>
#include <type_traits>

namespace challenge
{
	class ScriptFunction
	{
		friend class ScriptEngine;

	public:
		ScriptFunction(const std::string &signature, asIScriptContext *context, asIScriptModule *module);
		~ScriptFunction();

		template <typename T> T GetReturnValue();
		template<> float GetReturnValue<float>();
		template<> double GetReturnValue<double>();
		template<> bool GetReturnValue<bool>();
		template<> int8_t GetReturnValue<int8_t>();
		template<> int16_t GetReturnValue<int16_t>();
		template<> int32_t GetReturnValue<int32_t>();
		template<> int64_t GetReturnValue<int64_t>();
		template<> uint8_t GetReturnValue<uint8_t>();
		template<> uint16_t GetReturnValue<uint16_t>();
		template<> uint32_t GetReturnValue<uint32_t>();
		template<> uint64_t GetReturnValue<uint64_t>();

		template<typename... Args>
		void Call(Args... args);

	private:
		asIScriptContext *mContext;
		asIScriptFunction *mFunction;
		int mParamIndex;

		template <typename T> void SetParam(const T &param);
		template<> void SetParam<float>(const float &param);
		template<> void SetParam<double>(const double &param);
		template<> void SetParam<bool>(const bool &param);
		template<> void SetParam<int8_t>(const int8_t &param);
		template<> void SetParam<int16_t>(const int16_t &param);
		template<> void SetParam<int32_t>(const int32_t &param);
		template<> void SetParam<int64_t>(const int64_t &param);
		template<> void SetParam<uint8_t>(const uint8_t &param);
		template<> void SetParam<uint16_t>(const uint16_t &param);
		template<> void SetParam<uint32_t>(const uint32_t &param);
		template<> void SetParam<uint64_t>(const uint64_t &param);

		void SetParamArgs() 
		{
		}

		template <typename T>
		void SetParamArgs(T &param);

		template <typename T, typename... Rest> 
		void SetParamArgs(T &param, Rest... rest);
	};
}

#include <Challenge/Scripting/ScriptFunction.inl>


