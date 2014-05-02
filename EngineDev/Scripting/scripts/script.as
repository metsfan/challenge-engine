void printMap(map<uint64, uint64> @someMap)
{
	someMap.begin();
	print("size: " + someMap.size());

	someMap.erase(5);

	while (someMap.hasNext()) {
		uint64 key = someMap.next();
		uint64 value = someMap[key];

		print("key: " + key + ", value: " + value);
	}

	someMap.clear();
	print("size: " + someMap.size());

	someMap.insert(0, 10);
}

uint64 tester(int x)
{
	/*vector<int> testArray;

	testArray.push_back(11);
	testArray.push_back(12);
	testArray.push_back(13);

	testArray[1] = 27;*/

	map<uint64, uint64> testMap;
	//map<int, int> testMap;
	for (int i = 0; i < 10; i++) {
		testMap.insert(i, i * 3);
	}

	//testMap.insert(50, 30);

	
	//print("printing map");
	printMap(testMap);
	//print("map printed");
	//vectint key, value;turn testMap[6][0];
	uint64 retval = testMap[0];

	return retval;
}