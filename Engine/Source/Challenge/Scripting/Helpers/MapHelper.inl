#include <Challenge/Scripting/Helpers/MapHelper.h>
#include <Challenge/Scripting/Helpers/ScriptBasics.h>

namespace challenge
{

	class _MapIterStore
	{
	public:
		template <typename K, typename V>
		static typename std::map<K, V>::iterator NextIter(std::map<K, V> &map, bool begin, bool peek)
		{
			static std::map<std::map<K, V> *, std::map<K, V>::iterator> iters;
			std::lock_guard<std::mutex> lock(mMutex);

			if (!begin) {
				auto &it = iters.find(&map);
				if (it != iters.end()) {
					auto outIt = it->second;
					if (!peek) {
						it->second++;
					}

					if (outIt == map.end()) {
						// Make a copy before we erase
						outIt = it->second;
						iters.erase(&map);
					}

					return outIt;
				}
				else {
					iters[&map] = map.begin();
					return map.begin();
				}
			}
			else {
				iters[&map] = map.begin();
				return map.begin();
			}
		}

	private:
		static std::mutex mMutex;
	};

	std::mutex _MapIterStore::mMutex;

	class _MapHelper
	{
	public:
		template <typename K, typename V>
		static void insert(std::map<K, V> &map, K &key, V &value)
		{
			map[key] = value;
		}

		template <typename K, typename V>
		static V& opIndex(std::map<K, V> &map, K &key)
		{
			return map[key];
		}

		template <typename K, typename V>
		static std::map<K, V>& assign(std::map<K, V> &map, std::map<K, V> &other)
		{
			map = other;
			return map;
		}

		template <typename K, typename V>
		static int size(std::map<K, V> &map)
		{
			return map.size();
		}

		template <typename K, typename V>
		static void clear(std::map<K, V> &map)
		{
			return map.clear();
		}

		template <typename K, typename V>
		static void begin(std::map<K, V> &map)
		{
			_MapIterStore::NextIter<K, V>(map, true, false);
		}

		template <typename K, typename V>
		static std::pair<const K, V>& next(std::map<K, V> &map)
		{
			return *(_MapIterStore::NextIter<K, V>(map, false, false));
		}

		template <typename K, typename V>
		static bool hasNext(std::map<K, V> &map)
		{
			return _MapIterStore::NextIter<K, V>(map, false, true) != map.end();
		}
	};

	template <typename K, typename V>
	void MapHelper::Register(asIScriptEngine *engine, const std::string &keyName, 
		const std::string &valueName, std::string mapName)
	{
		std::string fn;

		if (mapName.length() == 0) {
			mapName = "map_" + keyName + "_" + valueName;
		}

		std::string pairName = mapName + "_pair";

		typedef std::map<K, V> MapType;
		typedef std::pair<K, V> PairType;

		engine->RegisterObjectType(pairName.c_str(), sizeof(PairType), asOBJ_VALUE | asOBJ_POD);
		fn = keyName + " first";
		engine->RegisterObjectProperty(pairName.c_str(), fn.c_str(), asOFFSET(PairType, first));
		fn = valueName + " second";
		engine->RegisterObjectProperty(pairName.c_str(), fn.c_str(), asOFFSET(PairType, second));

		engine->RegisterObjectType(mapName.c_str(), sizeof(MapType), asOBJ_VALUE | asOBJ_APP_CLASS);

		engine->RegisterObjectBehaviour(mapName.c_str(), asBEHAVE_CONSTRUCT, "void f()",
			asFUNCTION(ScriptBasics::Construct<MapType>), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectBehaviour(mapName.c_str(), asBEHAVE_DESTRUCT, "void f()",
			asFUNCTION(ScriptBasics::Destruct<MapType>), asCALL_CDECL_OBJFIRST);

		fn = "void insert(" + keyName + " &in, " + valueName + " &in)";
		engine->RegisterObjectMethod(mapName.c_str(), fn.c_str(), asFUNCTION((_MapHelper::insert<K, V>)), asCALL_CDECL_OBJFIRST);
		fn = valueName + "& opIndex(" + keyName + " &in)";
		engine->RegisterObjectMethod(mapName.c_str(), fn.c_str(), asFUNCTION((_MapHelper::opIndex<K, V>)), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectMethod(mapName.c_str(), "int size()", asFUNCTION((_MapHelper::size<K, V>)), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectMethod(mapName.c_str(), "void clear()", asFUNCTION((_MapHelper::clear<K, V>)), asCALL_CDECL_OBJFIRST);
		fn = "void opAssign(const " + mapName + " &in)";
		engine->RegisterObjectMethod(mapName.c_str(), fn.c_str(), asFUNCTION((_MapHelper::assign<K, V>)), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectMethod(mapName.c_str(), "void begin()", asFUNCTION((_MapHelper::begin<K, V>)), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectMethod(mapName.c_str(), "bool hasNext()", asFUNCTION((_MapHelper::hasNext<K, V>)), asCALL_CDECL_OBJFIRST);
		fn = pairName + "& next()";
		engine->RegisterObjectMethod(mapName.c_str(), fn.c_str(), asFUNCTION((_MapHelper::next<K, V>)), asCALL_CDECL_OBJFIRST);

		
	}
}