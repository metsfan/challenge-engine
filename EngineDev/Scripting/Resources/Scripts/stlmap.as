void printMap(map_int_float &in aMap)
{
	aMap.begin();
	while (aMap.hasNext()) {
		map_int_float_pair pair = aMap.next();

		print("Key: " + pair.first + ", Value: " + pair.second);
	}
}

float main(map_int_float &in aMap)
{
	aMap.insert(5, 7.3f);

	printMap(aMap);

	return 4.3f;
}