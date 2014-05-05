#include <Challenge/Scripting/ScriptEngine.h>
#include <Challenge/Scripting/ScriptModule.h>

namespace challenge
{
	template <typename T> T ScriptFunction::GetReturnValue()
	{
		T object = reinterpret_cast<T>(mContext->GetReturnObject());
		return object;
	}

	template <> float ScriptFunction::GetReturnValue<float>()
	{
		return mContext->GetReturnFloat();
	}

	template<> double ScriptFunction::GetReturnValue<double>()
	{
		return mContext->GetReturnDouble();
	}

	template<> bool ScriptFunction::GetReturnValue<bool>()
	{
		return mContext->GetReturnByte();
	}

	template<> int8_t ScriptFunction::GetReturnValue<int8_t>()
	{
		return mContext->GetReturnByte();
	}

	template<> int16_t ScriptFunction::GetReturnValue<int16_t>()
	{
		return mContext->GetReturnWord();
	}

	template<> int32_t ScriptFunction::GetReturnValue<int32_t>()
	{
		return mContext->GetReturnDWord();
	}

	template<> int64_t ScriptFunction::GetReturnValue<int64_t>()
	{
		return mContext->GetReturnQWord();
	}

	template<> uint8_t ScriptFunction::GetReturnValue<uint8_t>()
	{
		return mContext->GetReturnByte();
	}

	template<> uint16_t ScriptFunction::GetReturnValue<uint16_t>()
	{
		return mContext->GetReturnWord();
	}

	template<> uint32_t ScriptFunction::GetReturnValue<uint32_t>()
	{
		return mContext->GetReturnDWord();
	}

	template<> uint64_t ScriptFunction::GetReturnValue<uint64_t>()
	{
		return mContext->GetReturnQWord();
	}

	template<typename ReturnType, typename... Args>
	ReturnType ScriptFunction::Call(Args... args)
	{
		int result;

		mParamIndex = 0;

		result = mContext->Prepare(mFunction);

		SetParamArgs(args...);

		result = mContext->Execute();

		return GetReturnValue<ReturnType>();
	}

	template <typename T>
	void ScriptFunction::SetParamArgs(T &param)
	{
		this->SetParam(param);
	}

	template <typename T, typename... Rest>
	void ScriptFunction::SetParamArgs(T &param, Rest... rest)
	{
		this->SetParam(param);
		this->SetParamArgs(rest...);
	}

	template <typename T> void ScriptFunction::SetParam(const T &param)
	{
		// Only pointer types are acceptable here
		static_assert(std::is_pointer<T>::value, "AngelScript only accepts primitives and pointer types");

		int paramIndex = mParamIndex++;
		// Try to set as an object, if that fails, set as an address
		//int typeId = mFunction->GetParamTypeId(paramIndex);
		int result = mContext->SetArgObject(paramIndex, param);
		if (result < 0) {
			mContext->SetArgAddress(paramIndex, param);
		}
	}

	template<> void ScriptFunction::SetParam<float>(const float &param)
	{
		mContext->SetArgFloat(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<double>(const double &param)
	{
		mContext->SetArgDouble(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<bool>(const bool &param)
	{
		mContext->SetArgByte(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<int8_t>(const int8_t &param)
	{
		mContext->SetArgByte(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<int16_t>(const int16_t &param)
	{
		mContext->SetArgWord(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<int32_t>(const int32_t &param)
	{
		mContext->SetArgDWord(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<int64_t>(const int64_t &param)
	{
		mContext->SetArgQWord(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<uint8_t>(const uint8_t &param)
	{
		mContext->SetArgByte(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<uint16_t>(const uint16_t &param)
	{
		mContext->SetArgWord(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<uint32_t>(const uint32_t &param)
	{
		mContext->SetArgDWord(mParamIndex++, param);
	}

	template<> void ScriptFunction::SetParam<uint64_t>(const uint64_t &param)
	{
		mContext->SetArgQWord(mParamIndex++, param);
	}

	template<> void ScriptFunction::GetReturnValue<void>()
	{
	}
}