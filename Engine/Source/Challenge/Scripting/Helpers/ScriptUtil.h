#pragma once

#include <Challenge/Challenge.h>

#include <angelscript/angelscript.h>

namespace challenge
{
	class ScriptUtil
	{
	public:
		static bool IsPrimitiveType(int typeId)
		{
			return !(typeId & asTYPEID_HANDLETOCONST ||
				typeId & asTYPEID_APPOBJECT ||
				typeId & asTYPEID_MASK_OBJECT ||
				typeId & asTYPEID_OBJHANDLE ||
				typeId & asTYPEID_SCRIPTOBJECT);
		}
	};
};